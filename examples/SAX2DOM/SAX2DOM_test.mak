# Microsoft Developer Studio Generated NMAKE File, Based on SAX2DOM_test.dsp
!IF "$(CFG)" == ""
CFG=example_SAX2DOMTests - Win32 Debug
!MESSAGE No configuration specified. Defaulting to example_SAX2DOMTests - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "example_SAX2DOMTests - Win32 Release" && "$(CFG)" != "example_SAX2DOMTests - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"

OUTDIR=.\..\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SAX2DOM_test.exe"

!ELSE 

ALL : "ArabicaLib - Win32 Release" "$(OUTDIR)\SAX2DOM_test.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ArabicaLib - Win32 ReleaseCLEAN" 
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

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
	"..\..\lib\Arabica.lib"

"$(OUTDIR)\SAX2DOM_test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"

OUTDIR=.\..\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SAX2DOM_test.exe" "$(OUTDIR)\SAX2DOM_test.bsc"

!ELSE 

ALL : "ArabicaLib - Win32 Debug" "$(OUTDIR)\SAX2DOM_test.exe" "$(OUTDIR)\SAX2DOM_test.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ArabicaLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\test_Attribute.obj"
	-@erase "$(INTDIR)\test_Attribute.sbr"
	-@erase "$(INTDIR)\test_Document.obj"
	-@erase "$(INTDIR)\test_Document.sbr"
	-@erase "$(INTDIR)\test_DocumentFragment.obj"
	-@erase "$(INTDIR)\test_DocumentFragment.sbr"
	-@erase "$(INTDIR)\test_DocumentType.obj"
	-@erase "$(INTDIR)\test_DocumentType.sbr"
	-@erase "$(INTDIR)\test_DOMImplementation.obj"
	-@erase "$(INTDIR)\test_DOMImplementation.sbr"
	-@erase "$(INTDIR)\test_Element.obj"
	-@erase "$(INTDIR)\test_Element.sbr"
	-@erase "$(INTDIR)\test_ProcessingInstruction.obj"
	-@erase "$(INTDIR)\test_ProcessingInstruction.sbr"
	-@erase "$(INTDIR)\test_SAX.obj"
	-@erase "$(INTDIR)\test_SAX.sbr"
	-@erase "$(INTDIR)\test_Siblings.obj"
	-@erase "$(INTDIR)\test_Siblings.sbr"
	-@erase "$(INTDIR)\TestCase.obj"
	-@erase "$(INTDIR)\TestCase.sbr"
	-@erase "$(INTDIR)\TestFailure.obj"
	-@erase "$(INTDIR)\TestFailure.sbr"
	-@erase "$(INTDIR)\TestResult.obj"
	-@erase "$(INTDIR)\TestResult.sbr"
	-@erase "$(INTDIR)\TestSuite.obj"
	-@erase "$(INTDIR)\TestSuite.sbr"
	-@erase "$(INTDIR)\TextTestResult.obj"
	-@erase "$(INTDIR)\TextTestResult.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SAX2DOM_test.bsc"
	-@erase "$(OUTDIR)\SAX2DOM_test.exe"
	-@erase "$(OUTDIR)\SAX2DOM_test.ilk"
	-@erase "$(OUTDIR)\SAX2DOM_test.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SAX2DOM_test.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\test_Attribute.sbr" \
	"$(INTDIR)\test_Document.sbr" \
	"$(INTDIR)\test_DocumentFragment.sbr" \
	"$(INTDIR)\test_DocumentType.sbr" \
	"$(INTDIR)\test_DOMImplementation.sbr" \
	"$(INTDIR)\test_Element.sbr" \
	"$(INTDIR)\test_ProcessingInstruction.sbr" \
	"$(INTDIR)\test_SAX.sbr" \
	"$(INTDIR)\test_Siblings.sbr" \
	"$(INTDIR)\TestCase.sbr" \
	"$(INTDIR)\TestFailure.sbr" \
	"$(INTDIR)\TestResult.sbr" \
	"$(INTDIR)\TestSuite.sbr" \
	"$(INTDIR)\TextTestResult.sbr"

"$(OUTDIR)\SAX2DOM_test.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

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
	"..\..\lib\Arabica.lib"

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


!IF "$(CFG)" == "example_SAX2DOMTests - Win32 Release" || "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_Attribute.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_Attribute.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_Attribute.obj"	"$(INTDIR)\test_Attribute.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_Document.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_Document.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_Document.obj"	"$(INTDIR)\test_Document.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_DocumentFragment.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_DocumentFragment.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_DocumentFragment.obj"	"$(INTDIR)\test_DocumentFragment.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_DocumentType.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_DocumentType.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_DocumentType.obj"	"$(INTDIR)\test_DocumentType.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_DOMImplementation.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_DOMImplementation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_DOMImplementation.obj"	"$(INTDIR)\test_DOMImplementation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_Element.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_Element.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_Element.obj"	"$(INTDIR)\test_Element.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_ProcessingInstruction.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_ProcessingInstruction.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_ProcessingInstruction.obj"	"$(INTDIR)\test_ProcessingInstruction.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_SAX.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_SAX.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_SAX.obj"	"$(INTDIR)\test_SAX.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\test_Siblings.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\test_Siblings.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\test_Siblings.obj"	"$(INTDIR)\test_Siblings.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CppUnit\framework\TestCase.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\TestCase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\TestCase.obj"	"$(INTDIR)\TestCase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CppUnit\framework\TestFailure.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\TestFailure.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\TestFailure.obj"	"$(INTDIR)\TestFailure.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CppUnit\framework\TestResult.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\TestResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\TestResult.obj"	"$(INTDIR)\TestResult.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CppUnit\framework\TestSuite.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\TestSuite.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\TestSuite.obj"	"$(INTDIR)\TestSuite.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CppUnit\textui\TextTestResult.cpp

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"


"$(INTDIR)\TextTestResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"


"$(INTDIR)\TextTestResult.obj"	"$(INTDIR)\TextTestResult.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "example_SAX2DOMTests - Win32 Release"

"ArabicaLib - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Release" 
   cd "..\EXAMPLES\SAX2DOM"

"ArabicaLib - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ELSEIF  "$(CFG)" == "example_SAX2DOMTests - Win32 Debug"

"ArabicaLib - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Debug" 
   cd "..\EXAMPLES\SAX2DOM"

"ArabicaLib - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\EXAMPLES\SAX2DOM"

!ENDIF 


!ENDIF 

