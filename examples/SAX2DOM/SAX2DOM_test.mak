# Microsoft Developer Studio Generated NMAKE File, Based on SAX2DOM_test.dsp
!IF "$(CFG)" == ""
CFG=SAX2DOM_test - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SAX2DOM_test - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SAX2DOM_test - Win32 Release" && "$(CFG)" != "SAX2DOM_test - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SAX2DOM_test.mak" CFG="SAX2DOM_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SAX2DOM_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SAX2DOM_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SAX2DOM_test - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SAX2DOM_test.exe"

!ELSE 

ALL : "SAXlib - Win32 Release" "DOM - Win32 Release" "$(OUTDIR)\SAX2DOM_test.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"DOM - Win32 ReleaseCLEAN" "SAXlib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\test_Attribute.obj"
	-@erase "$(INTDIR)\test_Document.obj"
	-@erase "$(INTDIR)\test_DocumentFragment.obj"
	-@erase "$(INTDIR)\test_DocumentType.obj"
	-@erase "$(INTDIR)\test_DOMImplementation.obj"
	-@erase "$(INTDIR)\test_Element.obj"
	-@erase "$(INTDIR)\test_ProcessingInstruction.obj"
	-@erase "$(INTDIR)\test_SAX.obj"
	-@erase "$(INTDIR)\test_Siblings.obj"
	-@erase "$(INTDIR)\TestCase.obj"
	-@erase "$(INTDIR)\TestFailure.obj"
	-@erase "$(INTDIR)\TestResult.obj"
	-@erase "$(INTDIR)\TestSuite.obj"
	-@erase "$(INTDIR)\TextTestResult.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SAX2DOM_test.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SAX2DOM_test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SAX2DOM_test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SAX2DOM_test.pdb" /machine:I386 /out:"$(OUTDIR)\SAX2DOM_test.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\test_Attribute.obj" \
	"$(INTDIR)\test_Document.obj" \
	"$(INTDIR)\test_DocumentFragment.obj" \
	"$(INTDIR)\test_DocumentType.obj" \
	"$(INTDIR)\test_DOMImplementation.obj" \
	"$(INTDIR)\test_Element.obj" \
	"$(INTDIR)\test_ProcessingInstruction.obj" \
	"$(INTDIR)\test_SAX.obj" \
	"$(INTDIR)\test_Siblings.obj" \
	"$(INTDIR)\TestCase.obj" \
	"$(INTDIR)\TestFailure.obj" \
	"$(INTDIR)\TestResult.obj" \
	"$(INTDIR)\TestSuite.obj" \
	"$(INTDIR)\TextTestResult.obj" \
	"..\..\lib\SAX.lib" \
	"..\..\lib\Utilities.lib" \
	"..\..\SAX\Release\SAX.lib"

"$(OUTDIR)\SAX2DOM_test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SAX2DOM_test - Win32 Debug"

OUTDIR=.\..\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SAX2DOM_test.exe"

!ELSE 

ALL : "SAXlib - Win32 Debug" "DOM - Win32 Debug" "$(OUTDIR)\SAX2DOM_test.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"DOM - Win32 DebugCLEAN" "SAXlib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\test_Attribute.obj"
	-@erase "$(INTDIR)\test_Document.obj"
	-@erase "$(INTDIR)\test_DocumentFragment.obj"
	-@erase "$(INTDIR)\test_DocumentType.obj"
	-@erase "$(INTDIR)\test_DOMImplementation.obj"
	-@erase "$(INTDIR)\test_Element.obj"
	-@erase "$(INTDIR)\test_ProcessingInstruction.obj"
	-@erase "$(INTDIR)\test_SAX.obj"
	-@erase "$(INTDIR)\test_Siblings.obj"
	-@erase "$(INTDIR)\TestCase.obj"
	-@erase "$(INTDIR)\TestFailure.obj"
	-@erase "$(INTDIR)\TestResult.obj"
	-@erase "$(INTDIR)\TestSuite.obj"
	-@erase "$(INTDIR)\TextTestResult.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SAX2DOM_test.exe"
	-@erase "$(OUTDIR)\SAX2DOM_test.ilk"
	-@erase "$(OUTDIR)\SAX2DOM_test.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SAX2DOM_test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SAX2DOM_test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SAX2DOM_test.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SAX2DOM_test.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"\work\lib\vc6" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\test_Attribute.obj" \
	"$(INTDIR)\test_Document.obj" \
	"$(INTDIR)\test_DocumentFragment.obj" \
	"$(INTDIR)\test_DocumentType.obj" \
	"$(INTDIR)\test_DOMImplementation.obj" \
	"$(INTDIR)\test_Element.obj" \
	"$(INTDIR)\test_ProcessingInstruction.obj" \
	"$(INTDIR)\test_SAX.obj" \
	"$(INTDIR)\test_Siblings.obj" \
	"$(INTDIR)\TestCase.obj" \
	"$(INTDIR)\TestFailure.obj" \
	"$(INTDIR)\TestResult.obj" \
	"$(INTDIR)\TestSuite.obj" \
	"$(INTDIR)\TextTestResult.obj" \
	"..\..\lib\SAX.lib" \
	"..\..\lib\Utilities.lib"

"$(OUTDIR)\SAX2DOM_test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SAX2DOM_test.dep")
!INCLUDE "SAX2DOM_test.dep"
!ELSE 
!MESSAGE Warning: cannot find "SAX2DOM_test.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SAX2DOM_test - Win32 Release" || "$(CFG)" == "SAX2DOM_test - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_Attribute.cpp

"$(INTDIR)\test_Attribute.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_Document.cpp

"$(INTDIR)\test_Document.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_DocumentFragment.cpp

"$(INTDIR)\test_DocumentFragment.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_DocumentType.cpp

"$(INTDIR)\test_DocumentType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_DOMImplementation.cpp

"$(INTDIR)\test_DOMImplementation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_Element.cpp

"$(INTDIR)\test_Element.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_ProcessingInstruction.cpp

"$(INTDIR)\test_ProcessingInstruction.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_SAX.cpp

"$(INTDIR)\test_SAX.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test_Siblings.cpp

"$(INTDIR)\test_Siblings.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CppUnit\framework\TestCase.cpp

"$(INTDIR)\TestCase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CppUnit\framework\TestFailure.cpp

"$(INTDIR)\TestFailure.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CppUnit\framework\TestResult.cpp

"$(INTDIR)\TestResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CppUnit\framework\TestSuite.cpp

"$(INTDIR)\TestSuite.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CppUnit\textui\TextTestResult.cpp

"$(INTDIR)\TextTestResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "SAX2DOM_test - Win32 Release"

"DOM - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\DOM"
   $(MAKE) /$(MAKEFLAGS) /F .\DOM.mak CFG="DOM - Win32 Release" 
   cd "..\EXAMPLES\SAX2DOM"

"DOM - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\DOM"
   $(MAKE) /$(MAKEFLAGS) /F .\DOM.mak CFG="DOM - Win32 Release" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ELSEIF  "$(CFG)" == "SAX2DOM_test - Win32 Debug"

"DOM - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\DOM"
   $(MAKE) /$(MAKEFLAGS) /F .\DOM.mak CFG="DOM - Win32 Debug" 
   cd "..\EXAMPLES\SAX2DOM"

"DOM - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\DOM"
   $(MAKE) /$(MAKEFLAGS) /F .\DOM.mak CFG="DOM - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ENDIF 

!IF  "$(CFG)" == "SAX2DOM_test - Win32 Release"

"SAXlib - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" 
   cd "..\EXAMPLES\SAX2DOM"

"SAXlib - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ELSEIF  "$(CFG)" == "SAX2DOM_test - Win32 Debug"

"SAXlib - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" 
   cd "..\EXAMPLES\SAX2DOM"

"SAXlib - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ENDIF 


!ENDIF 

