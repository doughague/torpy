/** \file      LogService.hh 
    \brief     Header for LogService class.
    \author    Doug Hague
    \date      21.06.2013
*/
#ifndef TP_LOGSERVICE_HH
#define TP_LOGSERVICE_HH

#include "Torpy/Common.hh"

namespace Torpy {

/** \enum eLogLevel Log message level. */
enum eLogLevel { 
  Verbose  = 0, 
  Debug    = 1, 
  Info     = 2, 
  Progress = 3, 
  Warning  = 4, 
  Error    = 5, 
  Fatal    = 6, 
  All      = 7
};

/** \enum eLogTopic Log message topic. */
enum eLogTopic { 
  None           = 1, 
  InputArguments = 2, 
  Evaluation     = 4, 
  ObjectHandling = 8, 
  DataHandling   = 16
};


/** \class LogService
    \brief Logging message service class.

    This class is inspired by and modified from  
    <a href="http://root.cern.ch/root/html/RooMsgService.html">RooMsgService</a>.
*/
class LogService {
public:
  static LogService &instance();
  virtual ~LogService();

  void setPrefix(const char* prefix);
  inline const char* prefix() const { return mPrefix.c_str(); }

  inline unsigned int msgCount() const { return _msgCount; }
  inline unsigned int msgCount(eLogLevel level) { return _levelCounts[level]; }

  // // Print level support for BC-related messages that are not 
  // // routed through LogService (such as Minuit printouts)
  // inline void setSilentMode(bool flag = true){ _silentMode = flag; }
  // inline bool silentMode() const { return _silentMode; }

  inline void setGlobalKillBelow(eLogLevel level){ _globalMinLevel = level; }
  inline eLogLevel globalKillBelow() const { return _globalMinLevel; }
  

  const char* lookUpLevelName(eLogLevel level) const;
  eLogLevel lookUpLevel(const char* levelName) const;

  const char* lookUpTopicName(eLogTopic topic) const;
  eLogTopic lookUpTopic(const char* topicName) const;

  int addStream(eLogLevel level, ostream* os = 0, int topic = 0xFFFFF);
  int addStream(eLogLevel level, const char* fileName, 
		bool append, int topic = 0xFFFFF);
  int redirectToFile(const char* fileName, bool append, int id = 0);
  void deleteStream(int id); 
  unsigned int numStreams() const { return _streams.size() ; }
  void setStreamStatus(int id, bool flag);
  bool getStreamStatus(int id) const;
  ostream& getStream(int id) const;

  ostream& log(eLogLevel level, eLogTopic topic);

private:
  LogService();
  LogService(const LogService&);
  LogService& operator=(const LogService&);

  int activeStream(eLogLevel level, eLogTopic topic);
  bool isActive(eLogLevel level, eLogTopic topic);

  struct StreamConfig {
  public:
    friend class LogService;
    inline void addTopic(eLogTopic newTopic) { topic |= newTopic; }
    inline void removeTopic(eLogTopic oldTopic) { topic &= ~oldTopic; }
    bool match(eLogLevel level, eLogTopic top);

    bool active;
    eLogLevel minLevel;
    int topic;
    ostream* os;
  };
  LogService::StreamConfig& getStreamConfig(int id);

  string mPrefix;
  unsigned int _msgCount;
  // bool _silentMode;
  eLogLevel _globalMinLevel;
  map<eLogLevel,string> _levelNames;
  map<eLogLevel,unsigned int> _levelCounts;
  map<eLogTopic,string> _topicNames;

  ostream* _devnull;
  vector<LogService::StreamConfig> _streams;
  map<string,ostream*> _files;
};

// Shortcut streamer definitions with topic 
#define loutD(t) LogService::instance().log(Debug,t) 
#define loutI(t) LogService::instance().log(Info,t) 
#define loutP(t) LogService::instance().log(Progress,t) 
#define loutW(t) LogService::instance().log(Warning,t) 
#define loutE(t) LogService::instance().log(Error,t) 
#define loutF(t) LogService::instance().log(Fatal,t)

} // end namespace BlowCh

#endif // end TP_LOGSERVICE_HH
