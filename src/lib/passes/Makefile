COREIRCONFIG ?= g++
CXX ?= g++

ifeq ($(COREIRCONFIG),g++)
CXX = g++
endif

ifeq ($(COREIRCONFIG),g++-4.9)
CXX = g++-4.9
endif

CXXFLAGS = -std=c++11  -Wall  -fPIC

ifdef COREDEBUG
CXXFLAGS += -O0 -g3 -D_GLIBCXX_DEBUG 
endif

HOME = ../../..
LPATH = -L$(HOME)/lib
INCS = -I$(HOME)/include -I.
SRCFILES = $(wildcard [^_]*.cpp)
OBJS = $(patsubst %.cpp,build/%.o,$(SRCFILES))

DYLIBS = build/passes.dylib
SOLIBS = build/passes.so

all: $(DYLIBS) $(SOLIBS)

so: $(SOLIBS)

dylib: $(DYLIBS)

clean:
	rm -rf build/*

build/passes.dylib: $(OBJS)
	$(CXX) -install_name "@rpath/libcoreir-passes.dylib" -dynamiclib $(LPATH) -lcoreir -o $@ $^
	cp $@ $(HOME)/lib/libcoreir-passes.dylib

build/passes.so: $(OBJS)
	$(CXX) -shared $(LPATH) -lcoreir -o $@ $^
	cp $@ $(HOME)/lib/libcoreir-passes.so

build/%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
