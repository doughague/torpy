/** \file      LogService.cxx 
    \brief     Source for LogService class.
    \author    Doug Hague
    \date      21.06.2013
*/
#include "Torpy/Exception.hh"   // exception handler
#include "Torpy/LogService.hh"  // this class

using std::ios_base;
using std::out_of_range;

namespace Torpy {

//_____________________________________________________________________________
/** Instanton. 
    Return a reference to a singleton object that is created the
    first time this method is called. Only one object will be
    constructed per session.
 */
LogService &LogService::instance() 
{
  static LogService _theLogInstance;
  return _theLogInstance;
}

//_____________________________________________________________________________
/** Private constructor. */
LogService::LogService() 
  : mPrefix("Torpy"),
    _msgCount(0),
    _globalMinLevel(Info),
    _levelNames(),
    _topicNames() 
{
  // level names
  _levelNames[Verbose]  = "Verbose";
  _levelNames[Debug]    = "Debug";
  _levelNames[Info]     = "Info";
  _levelNames[Progress] = "Progress";
  _levelNames[Warning]  = "Warning";
  _levelNames[Error]    = "Error";
  _levelNames[Fatal]    = "Fatal";
  _levelNames[All]      = "All";
  // level counts
  _levelCounts[Verbose]  = 0;
  _levelCounts[Debug]    = 0;
  _levelCounts[Info]     = 0;
  _levelCounts[Progress] = 0;
  _levelCounts[Warning]  = 0;
  _levelCounts[Error]    = 0;
  _levelCounts[Fatal]    = 0;

  // topic names
  _topicNames[None]           = "";
  _topicNames[InputArguments] = "InputArguments";
  _topicNames[Evaluation]     = "Evaluation";
  _topicNames[ObjectHandling] = "ObjectHandling";
  _topicNames[DataHandling]   = "DataHandling";

  // handy "empty file"
  _devnull = new ofstream("/dev/null");

  // add default stream
  addStream(Info);
}  

//_____________________________________________________________________________
/** Private copy constructor, intentionally not implemented. */
LogService::LogService(const LogService&) 
{}

//_____________________________________________________________________________
/** Private assignment operator, intentionally not implemented. */
LogService& LogService::operator=(const LogService&)
{
  return *this;
}

//_____________________________________________________________________________
/** Destructor. */
LogService::~LogService() 
{
  // Delete all ostreams we own;
  map<string,ostream*>::iterator it = _files.begin();
  for(; it != _files.end(); ++it){
    ((ofstream*)it->second)->close();
    delete it->second;
  }
  delete _devnull;
}  

//_____________________________________________________________________________
/** Set the prefix for messages. */
void LogService::setPrefix(const char* prefix)
{ 
  mPrefix = string(prefix); 
}

//_____________________________________________________________________________
/** Convert a message-level enum to a message-level name. */
const char* LogService::lookUpLevelName(eLogLevel level) const
{ 
  // use map::at, since it's const 
  // but it can throw an out-of-range exception
  try{
    return _levelNames.at(level).c_str();      
  } 
  catch(const out_of_range& oor) {
    // cerr << "Out of Range error: " << oor.what() << '\n';
    // return _levelNames.at(Debug).c_str(); 
    return ""; 
  }
  // return _levelNames[level].c_str(); 
}

//_____________________________________________________________________________
/** Convert a message-level name to a message-level enum. */
eLogLevel LogService::lookUpLevel(const char* levelName) const
{
  string sln(levelName);
  map<eLogLevel,string>::const_iterator it = _levelNames.begin();
  for(; it != _levelNames.end(); ++it)
    if(it->second == sln) 
      return it->first;
  return Verbose;
}

//_____________________________________________________________________________
/** Convert a message-topic enum to a message-topic name. */
const char* LogService::lookUpTopicName(eLogTopic topic) const
{ 
  // use map::at, since it's const 
  // but it can throw an out-of-range exception
  try{
    return _topicNames.at(topic).c_str();      
  } 
  catch(const out_of_range& oor) {
    // cerr << "Out of Range error: " << oor.what() << '\n';
    // return _topicNames.at(InputArguments).c_str(); 
    return ""; 
  }
  // return _topicNames[topic].c_str(); 
}

//_____________________________________________________________________________
/** Convert a message-topic name to a message-topic enum. */
eLogTopic LogService::lookUpTopic(const char* topicName) const
{
  string stn(topicName);
  map<eLogTopic,string>::const_iterator it = _topicNames.begin();
  for(; it != _topicNames.end(); ++it)
    if(it->second == stn) 
      return it->first;
  return InputArguments;
}

//_____________________________________________________________________________
/** Add a message logging stream to cout for message with given 
    eLogLevel or higher (i.e. more severe).

    \param level Minimum message level.
    \param os Out-stream (ostream) for messages.
    \param topic Restrict stream to messages on a given topic. Default is all topics.
*/
int LogService::addStream(eLogLevel level, ostream* os, int topic) 
{
  // Create new stream object
  StreamConfig newStream;
  // Store configuration info
  newStream.active   = true;
  newStream.minLevel = level;
  newStream.topic    = topic;

  if(!os || os->fail()){
    // none, or bad input stream: default to stdout
    newStream.os = &cout;
  }
  else newStream.os = os;

  // Add it to list of active streams
  _streams.push_back(newStream);

  // Return stream identifier
  return _streams.size()-1;
}

//_____________________________________________________________________________
/** Add a message logging file-stream for message with given 
    eLogLevel or higher (i.e. more severe).

    \param fileName Output filename for messages.
    \param level Minimum message level.
    \param append Append to the end of the file if true, otherwise overwrite the file.
    \param topic Restrict stream to messages on a given topic. Default is all topics.
*/
int LogService::addStream(eLogLevel level, const char* fileName, 
			     bool append, int topic) 
{
  ostream* ofs = 0;
  if(fileName && strlen(fileName)>0){
    // See if we already opened the file
    ofs = _files["outFile"];
    if(!ofs){
      // To given file name, create owned stream for it
      if(append) 
	ofs = new ofstream(fileName, ios_base::out | ios_base::ate | ios_base::app);
      else 
	ofs = new ofstream(fileName, ios_base::out);
      _files["outFile"] = ofs;
    } 
  }

  // Return stream identifier
  return addStream(level, ofs, topic);
}

//_____________________________________________________________________________
/** Redirect stream with unique id to output fileName. */
int LogService::redirectToFile(const char* fileName, bool append, int id)
{
  // get stream properties
  StreamConfig oldStream;
  oldStream.active   = getStreamConfig(id).active;
  oldStream.minLevel = getStreamConfig(id).minLevel;
  oldStream.topic    = getStreamConfig(id).topic;

  // delete old stream
  deleteStream(id);

  // add new file stream
  return addStream(oldStream.minLevel, fileName, append, oldStream.topic);
}

//_____________________________________________________________________________
/** Delete stream with given unique ID code. */
void LogService::deleteStream(int id) 
{
  vector<StreamConfig>::iterator it = _streams.begin();
  it += id;
  _streams.erase(it);
}

//_____________________________________________________________________________
/** (De)Activate stream with given unique ID. */
void LogService::setStreamStatus(int id, bool flag)
{
  if(id<0 || id>=static_cast<int>(_streams.size())){
    // cerr << "LogService::setStreamStatus() Error: invalid stream ID " << id << endl;
    return;
  }
  _streams[id].active = flag;
}

//_____________________________________________________________________________
/** Get activation status of stream with given unique ID. */
bool LogService::getStreamStatus(int id) const
{
  if(id<0 || id>=static_cast<int>(_streams.size())){
    // cerr << "LogService::setStreamStatus() Error: invalid stream ID " << id << endl;
    return false;
  }
  return _streams[id].active;
}

//_____________________________________________________________________________
/** Get stream with given unique ID. */
ostream& LogService::getStream(int id) const
{
  if(id<0 || id>=static_cast<int>(_streams.size())){
    // cerr << "LogService::setStreamStatus() Error: invalid stream ID " << id << endl;
    return *_devnull;
  }
  return *_streams.at(id).os;
}

//_____________________________________________________________________________
/** Get stream-config with given unique ID. */
LogService::StreamConfig& LogService::getStreamConfig(int id)
{
  if(id<0 || id>=static_cast<int>(_streams.size())){
    // cerr << "LogService::setStreamStatus() Error: invalid stream ID " << id << endl;
    return _streams[0];
  }
  return _streams[id];
}

//_____________________________________________________________________________
/** Find appropriate logging stream for message from given topic and message level */
int LogService::activeStream(eLogLevel level, eLogTopic topic)
{
  if(level < _globalMinLevel) return -1;
  for(unsigned int s=0; s<_streams.size(); s++)
    if(_streams[s].match(level,topic))
      return s;
  return -1;
}

//_____________________________________________________________________________
/** Check if logging is active for given topic/MsgLevel combination. */
bool LogService::isActive(eLogLevel level, eLogTopic topic)
{
  return (activeStream(level, topic) >= 0);
}

//_____________________________________________________________________________
/** Determine if message from given level on given topic is logged. */
bool LogService::StreamConfig::match(eLogLevel level, eLogTopic top)
{
  if(!active)          return false;
  if(level < minLevel) return false;
  if(!(topic & top))   return false;
  return true;
}

//_____________________________________________________________________________
/** Log a message to a stream. 
    \return C++ ostream associated with given message configuration
*/
ostream& LogService::log(eLogLevel level, eLogTopic topic)
{
  int as = activeStream(level, topic);
  if(as == -1) return *_devnull;

  // increment total nuber of messages
  _msgCount++;
  _levelCounts[level]++;

  // Flush any previous messages
  (*_streams[as].os).flush();

  // print message
  if(mPrefix=="")
    (*_streams[as].os) << "[#" << as << "] " << _levelNames[level] 
		       << ":" << _topicNames[topic]; // << " -- ";
  else
    (*_streams[as].os) << "[" << mPrefix << "] " << _levelNames[level] 
		       << ":" << _topicNames[topic]; // << " -- ";

  // None topic is special
  if(topic == None)
    (*_streams[as].os) << " ";
  else
    (*_streams[as].os) << " -- ";

  // return stream
  return (*_streams[as].os);
}

} // end namespace Torpy
