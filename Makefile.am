
ACLOCAL_AMFLAGS = -I m4

SUBDIRS= src examples tests

install-data-local:
	@echo "------------------------------------------------------------"
	@echo "Installing include files to $(includedir)"
	@echo "------------------------------------------------------------"
	for inc in `cd $(srcdir)/include && find . -type f -print | grep -v \.svn`; \
	  do $(INSTALL_HEADER) -D "$(srcdir)/include/$$inc" "$(includedir)/$$inc"; \
	done 

uninstall-local:
	@echo "------------------------------------------------------------"
	@echo "Removing include files from $(includedir)"
	@echo "------------------------------------------------------------"
	for inc in `cd $(srcdir)/include && find . -type f -print | grep -v \.svn`; \
	  do rm -rf "$(includedir)/$$inc"; \
	done 
	for dir in `cd $(srcdir)/include && find . -type d -print | grep -v \.svn`; \
	  do rm -rf "$(includedir)/$$dir"; \
	done 

DIST_SUBDIRS= src examples tests
EXTRA_DIST=vs7 \
           vs8 \
           include \
           tests/XSLT/testsuite \
           src/SAX/wrappers/saxexpat.cpp \
           src/SAX/wrappers/saxlibxml2.cpp \
           src/SAX/wrappers/saxxerces.cpp \
           src/Utils/impl/codecvt_specialisations.cpp 
dist-hook:
	find $(distdir) -print | grep \.svn | xargs rm -rf
	find $(distdir) -print | grep \~$ | xargs rm -rf
	rm $(distdir)/include/SAX/ArabicaConfig.h

pkgconfigdir = src/pkgconfig
pkgconfig_DATA = arabica.pc

docs:
	doxygen doc/arabica.dox
	@echo "------------------------------------------------------------"
	@echo "Generated documents to ./doc/html"
	@echo "------------------------------------------------------------"

