
#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : 
	cd SAX; make 
	cd Utils; make 
	cd XML; make 
	cd examples; make

# Cleaning up

clean :
	cd SAX; make clean
	cd Utils; make clean
	cd XML; make clean
	cd examples; make clean
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
