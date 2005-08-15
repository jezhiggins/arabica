# Microsoft Developer Studio Project File - Name="ArabicaLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ArabicaLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SAX.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SAX.mak" CFG="ArabicaLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ArabicaLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ArabicaLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ArabicaLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "..\\" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Arabica.lib"

!ELSEIF  "$(CFG)" == "ArabicaLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Arabica.lib"

!ENDIF 

# Begin Target

# Name "ArabicaLib - Win32 Release"
# Name "ArabicaLib - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AttributeList.h
# End Source File
# Begin Source File

SOURCE=.\Attributes.h
# End Source File
# Begin Source File

SOURCE=.\ContentHandler.h
# End Source File
# Begin Source File

SOURCE=.\DocumentHandler.h
# End Source File
# Begin Source File

SOURCE=.\DTDHandler.h
# End Source File
# Begin Source File

SOURCE=.\EntityResolver.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHandler.h
# End Source File
# Begin Source File

SOURCE=.\HandlerBase.h
# End Source File
# Begin Source File

SOURCE=.\InputSource.h
# End Source File
# Begin Source File

SOURCE=.\Locator.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\ParserConfig.h
# End Source File
# Begin Source File

SOURCE=.\SAXException.h
# End Source File
# Begin Source File

SOURCE=.\saxfwd.h
# End Source File
# Begin Source File

SOURCE=.\SAXNotRecognizedException.h
# End Source File
# Begin Source File

SOURCE=.\SAXNotSupportedException.h
# End Source File
# Begin Source File

SOURCE=.\SAXParseException.h
# End Source File
# Begin Source File

SOURCE=.\XMLFilter.h
# End Source File
# Begin Source File

SOURCE=.\XMLReader.h
# End Source File
# End Group
# Begin Group "Helpers"

# PROP Default_Filter ""
# Begin Group "Source"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\helpers\InputSourceResolver.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\helpers\AttributeDefaults.h
# End Source File
# Begin Source File

SOURCE=.\helpers\AttributeListImpl.h
# End Source File
# Begin Source File

SOURCE=.\helpers\AttributesImpl.h
# End Source File
# Begin Source File

SOURCE=.\helpers\AttributeTypes.h
# End Source File
# Begin Source File

SOURCE=.\helpers\CatchErrorHandler.h
# End Source File
# Begin Source File

SOURCE=.\helpers\DefaultHandler.h
# End Source File
# Begin Source File

SOURCE=.\helpers\FeatureNames.h
# End Source File
# Begin Source File

SOURCE=.\helpers\InputSourceResolver.h
# End Source File
# Begin Source File

SOURCE=.\helpers\LocatorImpl.h
# End Source File
# Begin Source File

SOURCE=.\helpers\NamespaceSupport.h
# End Source File
# Begin Source File

SOURCE=.\helpers\ParserAdaptor.h
# End Source File
# Begin Source File

SOURCE=.\helpers\PropertyNames.h
# End Source File
# Begin Source File

SOURCE=.\helpers\StringAdaptor.h
# End Source File
# Begin Source File

SOURCE=.\helpers\XMLFilterImpl.h
# End Source File
# End Group
# End Group
# Begin Group "ext"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ext\Attributes2.h
# End Source File
# Begin Source File

SOURCE=.\ext\DeclHandler.h
# End Source File
# Begin Source File

SOURCE=.\ext\DefaultHandler2.h
# End Source File
# Begin Source File

SOURCE=.\ext\LexicalHandler.h
# End Source File
# Begin Source File

SOURCE=.\ext\Locator2.h
# End Source File
# End Group
# Begin Group "Wrappers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wrappers\saxexpat.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxexpat.h
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxlibxml2.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxlibxml2.h
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxmsxml2.h
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxxerces.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\wrappers\saxxerces.h
# End Source File
# End Group
# Begin Group "Filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\filter\Writer.h
# End Source File
# End Group
# Begin Group "Parsers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\parsers\saxgarden.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Group "impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Utils\impl\codecvt_specialisations.h
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\iso88591_utf8.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\iso88591_utf8.h
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\ucs2_utf16.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\ucs2_utf16.h
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\ucs2_utf8.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\impl\ucs2_utf8.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Utils\base64codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\base64codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\convert_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\Utils\convertstream.h
# End Source File
# Begin Source File

SOURCE=..\Utils\iso88591utf8codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\iso88591utf8codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\rot13codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\rot13codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\socket_stream.h
# End Source File
# Begin Source File

SOURCE=..\XML\UnicodeCharacters.h
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16beucs2codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16beucs2codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16leucs2codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16leucs2codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16utf8codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\utf16utf8codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\utf8iso88591codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\utf8iso88591codecvt.h
# End Source File
# Begin Source File

SOURCE=..\Utils\utf8ucs2codecvt.cpp
# End Source File
# Begin Source File

SOURCE=..\Utils\utf8ucs2codecvt.h
# End Source File
# Begin Source File

SOURCE=..\XML\XMLCharacterClasses.cpp
# End Source File
# Begin Source File

SOURCE=..\XML\XMLCharacterClasses.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ArabicaConfig.S

!IF  "$(CFG)" == "ArabicaLib - Win32 Release"

# Begin Custom Build
InputPath=.\ArabicaConfig.S

"ArabicaConfig.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /TC  /EP ArabicaConfig.S > ArabicaConfig.h

# End Custom Build

!ELSEIF  "$(CFG)" == "ArabicaLib - Win32 Debug"

# Begin Custom Build
InputPath=.\ArabicaConfig.S

"ArabicaConfig.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /TC  /EP ArabicaConfig.S > ArabicaConfig.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParserConfig.S

!IF  "$(CFG)" == "ArabicaLib - Win32 Release"

# Begin Custom Build
InputPath=.\ParserConfig.S

BuildCmds= \
	cl /TC /D USE_MSXML /EP ParserConfig.S > ParserConfig.h \
	cl /TC /D USE_MSXML /EP saxlib.S > saxlib.cpp \
	

"ParserConfig.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"saxlib.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ArabicaLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\ParserConfig.S

BuildCmds= \
	cl /TC /D USE_EXPAT /EP ParserConfig.S > ParserConfig.h \
	cl /TC /D USE_EXPAT /EP saxlib.S > saxlib.cpp \
	

"ParserConfig.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"saxlib.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\saxlib.cpp
# End Source File
# Begin Source File

SOURCE=.\saxlib.S
# End Source File
# End Target
# End Project
