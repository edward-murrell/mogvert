SRCDIR = src
MANDIR = man

.PHONY: all install run clean

all:
	cd $(SRCDIR); make;
	cd $(MANDIR); make;

install: all
	cd $(SRCDIR); make install;
	cd $(MANDIR); make install;

run:
	cd $(SRCDIR); make run;

clean:
	cd $(SRCDIR); make clean;
	cd $(MANDIR); make clean;
