
#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : SAX, examples

SAX: dummy
	cd SAX; ${MAKE}

examples: dummy
	cd examples; ${MAKE}

# Cleaning up

clean :
	cd SAX; ${MAKE} clean
	cd examples; ${MAKE} clean
	rm -f arabica.tar.gz
	rm -f arabica.zip

dist: tar zip


tar: clean
	cd ..; tar zcvf arabica/arabica.tar.gz --exclude CVS arabica

zip: clean
	cd ..;  zip -rv9 arabica/arabica.zip arabica -x arabica/arabica.tar.gz -x \*/CVS/\*

dummy:
#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
