
-include Makefile.header

######################################
# High level rules
all : 
	cd src; ${MAKE}
	cd test; ${MAKE}
	cd examples; ${MAKE}

clean :
	cd src; ${MAKE} clean
	cd test; ${MAKE} clean
	cd examples; ${MAKE} clean
	rm -f arabica.tar.gz
	rm -f arabica.zip

dist: tar zip


tar: clean
	cd ..; tar zcvf arabica/arabica.tar.gz --exclude CVS arabica

zip: clean
	cd ..;  zip -rv9 arabica/arabica.zip arabica -x arabica/arabica.tar.gz -x \*/CVS/\*


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File


