
ACLOCAL_AMFLAGS = -I m4

SUBDIRS= src examples tests

install-data-local:
	@echo "------------------------------------------------------------"
	@echo "Installing include files to $(pkgincludedir)"
	@echo "------------------------------------------------------------"
	for inc in `cd $(srcdir)/include && find . -type f -print | grep -v \.svn`; \
	  do mkdir -p "`dirname \"$(pkgincludedir)/$$inc\"`"; $(INSTALL_HEADER) "$(srcdir)/include/$$inc" "$(pkgincludedir)/$$inc"; \
	done 
	$(INSTALL_HEADER) "$(top_builddir)/include/SAX/ArabicaConfig.hpp" "$(pkgincludedir)/SAX"

uninstall-local:
	@echo "------------------------------------------------------------"
	@echo "Removing include files from $(pkgincludedir)"
	@echo "------------------------------------------------------------"
	for inc in `cd $(srcdir)/include && find . -type f -print | grep -v \.svn`; \
	  do rm -rf "$(pkgincludedir)/$$inc"; \
	done 
	for dir in `cd $(srcdir)/include && find . -type d -print | grep -v \.svn`; \
	  do rm -rf "$(pkgincludedir)/$$dir"; \
	done 

DIST_SUBDIRS= src examples tests
EXTRA_DIST=vs7 \
           vs8 \
           vs9 \
           doc \
           include \
           tests/XSLT/testsuite \
           src/SAX/wrappers/saxexpat.cpp \
           src/SAX/wrappers/saxlibxml2.cpp \
           src/SAX/wrappers/saxxerces.cpp \
           src/convert/impl/codecvt_specialisations.cpp 
dist-hook:
	find $(distdir) -print | grep \.svn | xargs rm -rf
	find $(distdir) -print | grep \~$ | xargs rm -rf
	rm $(distdir)/include/SAX/ArabicaConfig.hpp

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = arabica.pc

docs:
	cd doc && doxygen arabica.dox
	@echo "------------------------------------------------------------"
	@echo "Generated documents to ./doc/html"
	@echo "------------------------------------------------------------"

