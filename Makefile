#################################################################
#                 GNU-Makefile for libTorpy                   #
#################################################################


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                      Build specifics                          
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Platform ------------------------------------------------------
# choose: linux, macos, win, arm
Platform = linux
# Architecture --------------------------------------------------
# choose: 0 for 32-bit, 1 for 64-bit
Is64bit = 1
# Debug ---------------------------------------------------------
# choose: 0 for deployment-mode, 1 for debug-mode
Debug = 0
# Static --------------------------------------------------------
# choose: 0 for shared-libs only, 1 for shared and static libs
Static = 0


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                       This Library                            
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Library Name --------------------------------------------------
LibName = Torpy
# Library Version -----------------------------------------------
Version = 0.1


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                           Generic                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Directories ---------------------------------------------------
# top ---
Local  = $(shell pwd)
IncDir = include
SrcDir = src
OutDir = cache
LibDir = lib
BinDir = bin
DocDir = doc
# sources ---
IncSrcDir = $(IncDir)/$(LibName)
LibSrcDir = $(SrcDir)/lib
ExeSrcDir = $(SrcDir)/progs
TstSrcDir = $(SrcDir)/tests

# Suffixes ------------------------------------------------------
HeadSuf = hh
SrcSuf  = cxx
ObjSuf  = o
DepSuf  = d
ExeSuf  =
ArcSuf  = a
DllSuf  = so
SptSuf  = C
# platform dependent suffixes ---
ifeq ($(Platform), macos)
	DllSuf = dylib
endif


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                           Aliases                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Library -------------------------------------------------------
LibApi     = $(IncSrcDir)/$(LibName).$(HeadSuf)
LibSrcs    = $(wildcard $(LibSrcDir)/*.$(SrcSuf))
LibObjsPic = $(patsubst %.$(SrcSuf),$(OutDir)/pic/%.$(ObjSuf),$(LibSrcs))
LibObjsPdc = $(patsubst %.$(SrcSuf),$(OutDir)/pdc/%.$(ObjSuf),$(LibSrcs))
LibSo      = $(LibDir)/lib$(LibName).$(DllSuf)
LibArPic   = $(LibDir)/lib$(LibName)pic.$(ArcSuf)
LibArPdc   = $(LibDir)/lib$(LibName).$(ArcSuf)

# Programs ------------------------------------------------------
ExeSrcs = $(wildcard $(ExeSrcDir)/*.$(SrcSuf))
ExeObjs = $(patsubst %.$(SrcSuf),$(OutDir)/pic/%.$(ObjSuf),$(ExeSrcs))
ExeBins = $(patsubst $(ExeSrcDir)/%.$(SrcSuf),$(BinDir)/%,$(ExeSrcs))

# Tests ---------------------------------------------------------
TstSrcs = $(wildcard $(TstSrcDir)/*.$(SrcSuf))
TstObjs = $(patsubst %.$(SrcSuf),$(OutDir)/pic/%.$(ObjSuf),$(TstSrcs))
TstBin  = $(BinDir)/tests

# All -----------------------------------------------------------
AllLibs = $(LibSo)
AllObjs = $(LibObjsPic) $(ExeObjs) $(TstObjs)
ifeq ($(Static), 1)
	AllLibs += $(LibArPic) $(LibArPdc) 
	AllObjs += $(LibObjsPdc)
endif

# Documentation -------------------------------------------------
DocDir   = doc
DoxyFile = $(DocDir)/Doxyfile
DoxyLog  = $(DocDir)/doxy.log
DoxyCmd  = $(shell which doxygen)
MainPage = $(LibSrcDir)/mainpage.$(SptSuf)
ifeq ($(Date),)
	Date = $(shell date +%d.%m.%Y)
endif


# Readme --------------------------------------------------------
Readme = Readme.md

# License -------------------------------------------------------
License = License.txt

# Distribution bundle -------------------------------------------
DistName = $(LibName)-v$(Version).tgz
DistDir  = $(LibName)-v$(Version)

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                         Flags                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Includes = -I. -I$(IncDir)
CXXFLAGS = -Wfatal-errors

# Arch ----------------------------------------------------------
ifeq ($(Is64bit), 1)
	CXXFLAGS += -m64
	LDFLAGS  += -m64
endif

# Debug ---------------------------------------------------------
ifeq ($(Debug), 1)
	CXXFLAGS += -g -O1 -DDEBUG -pedantic -Wall -Wextra -Wshadow -ftrapv -Wcast-align
else
	CXXFLAGS += -O3 -DNDEBUG
endif

# Linux ---------------------------------------------------------
ifeq ($(Platform), linux)
	SOFLAGS     = -shared -Wl,-soname,$(LibSo)
endif

# MacOSX --------------------------------------------------------
ifeq ($(Platform), macos)
	ProdVers    = $(shell sw_vers | sed -n 's/ProductVersion://p' | cut -d . -f 2)
	LDFLAGS     = -mmacosx-version-min=10.$(ProdVers)
	SOFLAGS     = -dynamiclib -single_module -undefined dynamic_lookup -install_name $(LibSo)
endif

# Windows -------------------------------------------------------
ifeq ($(Platform), win)
	$(error make for windows not implemented!)
endif

# ARM -----------------------------------------------------------
ifeq ($(Platform), arm)
	$(error make for ARM not implemented!)
endif


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                   External C/C++ Libraries                                  
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                        Main Targets                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
.PHONY : clean show help test doc clean-doc swig clean-swig 
all    : dirs print libs progs
libs   : $(AllLibs)
progs  : $(ExeObjs) $(ExeBins)
swig   : python java
clean  : clean-lib

# compile files: Possition Independent --------------------------
$(OutDir)/pic/%.$(ObjSuf): %.$(SrcSuf)
	@$(call compile,$@,$<,-fPIC)

# compile files: Possition Dependent ----------------------------
$(OutDir)/pdc/%.$(ObjSuf): %.$(SrcSuf)
	@$(call compile,$@,$<)

# shared lib ----------------------------------------------------
$(LibSo): $(LibObjsPic)
	@echo "\tLinking    "$@
	@$(CXX) $(LDFLAGS) $(SOFLAGS) $(ExSoLibs) $^ -o $@

# static lib w/ -fPIC -------------------------------------------
$(LibArPic): $(LibObjsPic)
	@echo "\tPacking    "$@
	@$(AR) rcs $@ $(ExArLibs) $^

# static lib w/o -fPIC ------------------------------------------
$(LibArPdc): $(LibObjsPdc)
	@echo "\tPacking    "$@
	@$(AR) rcs $@ $(ExArLibs) $^

# executable programs -------------------------------------------
$(BinDir)/%: $(OutDir)/pic/src/progs/%.$(ObjSuf) $(LibSo)
	@echo "\tLinking    "$@
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LibSo)

# run the test executable ---------------------------------------
test: $(TstBin)
	@echo "\tRunning    "$^	"..." $(shell ./$(TstBin))

# build the test executable -------------------------------------
$(TstBin): $(LibSo) $(TstObjs)
	@echo "\tLinking    "$@
	@$(CXX) $(CXXFLAGS) -o $(TstBin) $(TstObjs) $(LibSo)

# compile helper function ---------------------------------------
# $1 -> output object-file 
# $2 -> source-file 
# $3 -> additional flags
define compile
	mkdir -p $(OutDir)
	mkdir -p $(dir $1)
	echo "\tCompiling  $1"
	$(CXX) $(CXXFLAGS) $3 $(Includes) -MMD -MP -c -o $1 $2
endef

# include dependencies ------------------------------------------
-include $(AllObjs:%.o=%.d)



# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                    Other & Phony Targets                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# print some info -----------------------------------------------
print:
ifeq ($(LibSrcs),)
	$(error No source files found!)
else
	@echo "Building lib$(LibName) with:\n\t$(CXX)    $(CXXFLAGS)"
endif


# clean the library files ---------------------------------------
clean-lib: 
	@echo "\tCleaning   $(OutDir)/* $(LibDir)/* $(BinDir)/*"
	@rm -rf $(OutDir)/* $(LibDir)/* $(BinDir)/*

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                           Directories                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# directories ---------------------------------------------------
dirs:
	@$(call dirmk,$(IncDir))
	@$(call dirmk,$(SrcDir))
	@$(call dirmk,$(OutDir))
	@$(call dirmk,$(LibDir))
	@$(call dirmk,$(BinDir))
	@$(call dirmk,$(IncSrcDir))
	@$(call dirmk,$(LibSrcDir))
	@$(call dirmk,$(ExeSrcDir))
	@$(call dirmk,$(TstSrcDir))
	@$(call dirmk,$(DocDir))
	@$(call dirmk,$(DocDir)/html)

# directory creator helper function -----------------------------
# $1 -> directory
define dirmk
	if [ ! -d $1 ] && [ ! -h $1 ]; then mkdir -pv $1; fi;
endef


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                    Doxygen Documentation                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# documentation -------------------------------------------------
doc: $(AllLibs)
ifneq ($(DoxyCmd),)
	@echo "\tDoxygen    $(DocDir)/html/index.html"
	@doxygen $(DoxyFile) > $(DoxyLog)
else
	@echo "\tDoxygen    Not found!"
endif

# clean the documentation ---------------------------------------
clean-doc:
	@echo "\tCleaning   $(DocDir)/html/*"
	@rm -rf $(DocDir)/html/*


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#                           Information                             
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# show "variables" in this makefile -----------------------------
show:
	@echo "=============================================================="
	@echo "Project:"
	@echo "  Name     = $(LibName)"
	@echo "  Prefix   = $(Local)"
	@echo "  Version  = $(Version)"
	@echo "=============================================================="
	@echo "Objects:"
	@echo "  Sources   = $(LibSrcs)"
	@echo "  Libraries = $(AllLibs)"
	@echo "  Programs  = $(ExeBins)"
	@echo "=============================================================="
	@echo "Compilers:"
	@echo "  CXX      = $(CXX)"
	@echo "  CC       = $(CC)"
	@echo "  LD       = $(LD)"
	@echo "=============================================================="
	@echo "Flags:"
	@echo "  CXX      = $(CXXFLAGS)"
	@echo "  SO       = $(SOFLAGS)"
	@echo "  LD       = $(LDFLAGS)"
	@echo "=============================================================="

# print target help ---------------------------------------------
help:
	@echo "=============================================================="
	@echo "Targets:       Function:"
	@echo "  all          - (default) compile/link all libraries & executables"
	@echo "  clean        - delete all libs and execs"
	@echo "  doc          - generate doxygen documentation"
#	@echo "  dist         - bundle the source into a gzipped-tarball"
	@echo "  objs         - compile object libraries"
	@echo "  lib          - link objs & create shared object library"
	@echo "  progs        - compile & link executables"
	@echo "  test         - compile & run the test executable"
	@echo "  clean-doc    - clean the (html) documentation"
#	@echo "  install      - link library & executables to "$(InstallDir)
	@echo "  show         - show the flags, and files used"
	@echo "=============================================================="
