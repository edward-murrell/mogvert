INSTALL = /usr/bin/install
STRIP = /usr/bin/strip
BINARY=mogconvert
CXX=g++
LIBS= -lmp3lame -lvorbisfile -lvorbis -lao -lFLAC++
CXXFLAGS=-O3 -Wall -g -pipe -march=i686 -DHAVE_INTTYPES_H
OBJS=init.o error.o filehandler.o decoders/ogg.o decoders/flac.o encoders/mp3.o encoders/ao.o mogconvert.o
BINDIR=/usr/local/

.PHONY: all run clean install

.SUFFIXES:

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^

all: $(BINARY)

$(BINARY):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $(BINARY) $(OBJS)

install: all
	$(STRIP) $(BINARY)
	$(INSTALL) -s -m 0755 -o root -g root $(BINARY) $(BINDIR)/bin/$(BINARY)

run: $(BINARY)
	./$(BINARY)

clean:
	-rm -f $(OBJS) $(BINARY)
	-rm -f ../$(BINARY)
