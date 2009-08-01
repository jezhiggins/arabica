
cc_sources = arabica.cpp \
	SAX/helpers/InputSourceResolver.cpp \
	convert/base64codecvt.cpp \
	convert/impl/iso88591_utf8.cpp \
	convert/impl/ucs2_utf16.cpp \
	convert/impl/ucs2_utf8.cpp \
	convert/iso88591utf8codecvt.cpp \
	convert/rot13codecvt.cpp \
	convert/ucs2utf8codecvt.cpp \
	convert/utf16beucs2codecvt.cpp \
	convert/utf16leucs2codecvt.cpp \
	convert/utf16utf8codecvt.cpp \
	convert/utf8iso88591codecvt.cpp \
	convert/utf8ucs2codecvt.cpp \
        io/uri.cpp \
	XML/XMLCharacterClasses.cpp \
        taggle/Schema.cpp

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libarabica.la
libarabica_la_SOURCES= $(cc_sources) 
libarabica_la_LDFLAGS= @PARSER_LIBS@



