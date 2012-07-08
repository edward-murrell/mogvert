SRCDIR = src
MANDIR = man

.PHONY: all install run clean test

all:
	cd $(SRCDIR); make;
	cd $(MANDIR); make;

install: all
	cd $(SRCDIR); make install;
	cd $(MANDIR); make install;

test:	all
	cd $(SRCDIR); make test

run:
	cd $(SRCDIR); make run;

clean:
	cd $(SRCDIR); make clean;
	cd $(MANDIR); make clean;
