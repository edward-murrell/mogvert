COMPRESS = /bin/gzip
INSTALL = /usr/bin/install
MANDIR = /usr/man
MANPAGE = mogconvert.1

all:
	$(COMPRESS) -c $(MANPAGE) > $(MANPAGE).gz

install:
	$(INSTALL) -m 0644 -o root -g root $(MANPAGE).gz $(MANDIR)/man1/$(MANPAGE).gz

clean:
	rm -f $(MANPAGE).gz

