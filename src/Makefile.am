
cc_sources = arabica.cpp \
	SAX/helpers/InputSourceResolver.cpp \
	Utils/base64codecvt.cpp \
	Utils/impl/iso88591_utf8.cpp \
	Utils/impl/ucs2_utf16.cpp \
	Utils/impl/ucs2_utf8.cpp \
	Utils/iso88591utf8codecvt.cpp \
	Utils/rot13codecvt.cpp \
	Utils/ucs2utf8codecvt.cpp \
	Utils/utf16beucs2codecvt.cpp \
	Utils/utf16leucs2codecvt.cpp \
	Utils/utf16utf8codecvt.cpp \
	Utils/utf8iso88591codecvt.cpp \
	Utils/utf8ucs2codecvt.cpp \
        io/uri.cpp \
	XML/XMLCharacterClasses.cpp

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libarabica.la
libarabica_la_SOURCES= $(cc_sources) 
libarabica_la_LDFLAGS= @PARSER_LIBS@



