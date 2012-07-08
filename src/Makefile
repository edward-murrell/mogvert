INSTALL = /usr/bin/install
STRIP = /usr/bin/strip
BINARY=mogconvert
CXX=g++
LIBS= -lmp3lame -logg -lvorbisfile -lvorbis -lao -lFLAC -lFLAC++
CXXFLAGS= -Wall -g -pipe -DHAVE_INTTYPES_H
OBJS=init.o error.o filehandler.o decoders/ogg.o decoders/flac.o encoders/mp3.o encoders/ao.o 
OBJ_BIN=mogconvert.o
BINDIR=/usr/local/
TESTBINARY=test
OBJ_TEST=test.o

.PHONY: all run clean install

.SUFFIXES:

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^

all: $(BINARY)

$(BINARY):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BINARY) $(OBJS) $(OBJ_BIN) $(LIBS)

testbin: $(OBJ_TEST) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TESTBINARY) $(OBJS) $(OBJ_TEST) $(LIBS)

test: testbin
	./$(TESTBINARY)
	
	
install: all
	$(STRIP) $(BINARY)
	$(INSTALL) -s -m 0755 -o root -g root $(BINARY) $(BINDIR)/bin/$(BINARY)

run: $(BINARY)
	./$(BINARY)

clean:
	-rm -f $(OBJS) $(OBJ_BIN) $(OBJ_TEST) $(BINARY) $(TESTBINARY)
	-rm -f ../$(BINARY)
