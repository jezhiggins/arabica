ACLOCAL_AMFLAGS = -I m4

SUBDIRS=include src examples tests

DIST_SUBDIRS=include src examples tests 
EXTRA_DIST=vs7 \
           vs8 \
           vs9 \
           vs10 \
           doc \
           tests/XSLT/testsuite \
           src/SAX/wrappers/saxexpat.cpp \
           src/SAX/wrappers/saxlibxml2.cpp \
           src/SAX/wrappers/saxxerces.cpp \
           src/convert/impl/codecvt_specialisations.cpp 

dist-hook:
	find $(distdir) -print | grep \.bzr | xargs rm -rf
	find $(distdir) -print | grep \.svn | xargs rm -rf
	rm -f $(distdir)/include/SAX/ArabicaConfig.hpp

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = arabica.pc

docs:
	cd doc && doxygen arabica.dox
	@echo "------------------------------------------------------------"
	@echo "Generated documents to ./doc/html"
	@echo "------------------------------------------------------------"

