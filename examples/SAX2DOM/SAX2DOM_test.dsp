# Microsoft Developer Studio Project File - Name="example_SAX2DOMTests" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=example_SAX2DOMTests - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SAX2DOM_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SAX2DOM_test.mak" CFG="example_SAX2DOMTests - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "example_SAX2DOMTests - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "example_SAX2DOMTests - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\..\lib" /libpath:"\work\lib\vc6"

!ENDIF 

# Begin Target

# Name "example_SAX2DOMTests - Win32 Release"
# Name "example_SAX2DOMTests - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\test_Attribute.cpp
# End Source File
# Begin Source File

SOURCE=.\test_Document.cpp
# End Source File
# Begin Source File

SOURCE=.\test_DocumentFragment.cpp
# End Source File
# Begin Source File

SOURCE=.\test_DocumentType.cpp
# End Source File
# Begin Source File

SOURCE=.\test_DOMImplementation.cpp
# End Source File
# Begin Source File

SOURCE=.\test_Element.cpp
# End Source File
# Begin Source File

SOURCE=.\test_ProcessingInstruction.cpp
# End Source File
# Begin Source File

SOURCE=.\test_SAX.cpp
# End Source File
# Begin Source File

SOURCE=.\test_Siblings.cpp
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestCase.cpp
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestFailure.cpp
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestSuite.cpp
# End Source File
# Begin Source File

SOURCE=.\CppUnit\textui\TextTestResult.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CppUnit\framework\CppUnitException.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\estring.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\Guards.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\Test.h
# End Source File
# Begin Source File

SOURCE=.\test_Attribute.h
# End Source File
# Begin Source File

SOURCE=.\test_Document.h
# End Source File
# Begin Source File

SOURCE=.\test_DocumentFragment.h
# End Source File
# Begin Source File

SOURCE=.\test_DocumentType.h
# End Source File
# Begin Source File

SOURCE=.\test_DOMImplementation.h
# End Source File
# Begin Source File

SOURCE=.\test_Element.h
# End Source File
# Begin Source File

SOURCE=.\test_Notation.h
# End Source File
# Begin Source File

SOURCE=.\test_ProcessingInstruction.h
# End Source File
# Begin Source File

SOURCE=.\test_SAX.h
# End Source File
# Begin Source File

SOURCE=.\test_Siblings.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestCaller.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestCase.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestFailure.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestResult.h
# End Source File
# Begin Source File

SOURCE=.\CppUnit\framework\TestSuite.h
# End Source File
# End Group
# Begin Group "Libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\lib\Arabica.lib
# End Source File
# End Group
# End Target
# End Project
