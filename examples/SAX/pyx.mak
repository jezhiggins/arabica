# Microsoft Developer Studio Generated NMAKE File, Based on pyx.dsp
!IF "$(CFG)" == ""
CFG=pyx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to pyx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "pyx - Win32 Release" && "$(CFG)" != "pyx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pyx.mak" CFG="pyx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pyx - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pyx - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "pyx - Win32 Release"

OUTDIR=.\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\pyx.exe"

!ELSE 

ALL : "SAXlib - Win32 Release" "$(OUTDIR)\pyx.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SAXlib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\pyx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\pyx.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "..\SAXExpat" /I "..\SAXlibxml" /I "..\SAX" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\pyx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pyx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\pyx.pdb" /machine:I386 /out:"$(OUTDIR)\pyx.exe" 
LINK32_OBJS= \
	"$(INTDIR)\pyx.obj" \
	"..\..\lib\SAX.lib" \
	"..\..\SAX\Release\SAX.lib"

"$(OUTDIR)\pyx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pyx - Win32 Debug"

OUTDIR=.\..\..\bin
INTDIR=.\pyx___Win32_Debug
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\pyx.exe"

!ELSE 

ALL : "SAXlib - Win32 Debug" "$(OUTDIR)\pyx.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SAXlib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\pyx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\pyx.exe"
	-@erase "$(OUTDIR)\pyx.ilk"
	-@erase "$(OUTDIR)\pyx.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\pyx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pyx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\pyx.pdb" /debug /machine:I386 /out:"$(OUTDIR)\pyx.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"\work\lib\vc6" 
LINK32_OBJS= \
	"$(INTDIR)\pyx.obj" \
	"..\..\lib\SAX.lib"

"$(OUTDIR)\pyx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("pyx.dep")
!INCLUDE "pyx.dep"
!ELSE 
!MESSAGE Warning: cannot find "pyx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "pyx - Win32 Release" || "$(CFG)" == "pyx - Win32 Debug"
SOURCE=.\pyx.cpp

"$(INTDIR)\pyx.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "pyx - Win32 Release"

"SAXlib - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" 
   cd "..\examples\SAX"

"SAXlib - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ELSEIF  "$(CFG)" == "pyx - Win32 Debug"

"SAXlib - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" 
   cd "..\examples\SAX"

"SAXlib - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ENDIF 


!ENDIF 

