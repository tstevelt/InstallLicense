
PROG = InstallLicense
LIB = InstallLicense.a
XLIB = /usr/local/lib64/shslib.a
DEF = /usr/local/include
PRG = /usr/local/bin/$(PROG)

FILES = \
	$(LIB)(InstallLicense.o)	\
	$(LIB)(MainLicense.o)		\
	$(LIB)(IncludeLicense.o)	\
	$(LIB)(ProcessDirectory.o)	\
	$(LIB)(ProcessFile.o)		\
	$(LIB)(getargs.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): InstallLicense.h $(DEF)/shslib.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

