# Microsoft Developer Studio Generated NMAKE File, Based on SimpleHandler.dsp
!IF "$(CFG)" == ""
CFG=SimpleHandler - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SimpleHandler - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SimpleHandler - Win32 Release" && "$(CFG)" != "SimpleHandler - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleHandler.mak" CFG="SimpleHandler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleHandler - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SimpleHandler - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "SimpleHandler - Win32 Release"

OUTDIR=.\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleHandler.exe"

!ELSE 

ALL : "Utilities - Win32 Release" "SAXlib - Win32 Release" "$(OUTDIR)\SimpleHandler.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SAXlib - Win32 ReleaseCLEAN" "Utilities - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\SimpleHandler.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wrapper.obj"
	-@erase "$(OUTDIR)\SimpleHandler.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "..\SAX" /I "..\SAXExpat" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SimpleHandler.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleHandler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SimpleHandler.pdb" /machine:I386 /out:"$(OUTDIR)\SimpleHandler.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SimpleHandler.obj" \
	"$(INTDIR)\wrapper.obj" \
	"..\..\SAX\Release\SAX.lib" \
	"..\..\Utils\Release\Utilities.lib"

"$(OUTDIR)\SimpleHandler.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SimpleHandler - Win32 Debug"

OUTDIR=.\..\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleHandler.exe" "$(OUTDIR)\SimpleHandler.bsc"

!ELSE 

ALL : "Utilities - Win32 Debug" "SAXlib - Win32 Debug" "$(OUTDIR)\SimpleHandler.exe" "$(OUTDIR)\SimpleHandler.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SAXlib - Win32 DebugCLEAN" "Utilities - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\SimpleHandler.obj"
	-@erase "$(INTDIR)\SimpleHandler.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wrapper.obj"
	-@erase "$(INTDIR)\wrapper.sbr"
	-@erase "$(OUTDIR)\SimpleHandler.bsc"
	-@erase "$(OUTDIR)\SimpleHandler.exe"
	-@erase "$(OUTDIR)\SimpleHandler.ilk"
	-@erase "$(OUTDIR)\SimpleHandler.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /I "\work\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SimpleHandler.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleHandler.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SimpleHandler.sbr" \
	"$(INTDIR)\wrapper.sbr"

"$(OUTDIR)\SimpleHandler.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SimpleHandler.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SimpleHandler.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SimpleHandler.obj" \
	"$(INTDIR)\wrapper.obj" \
	"..\..\lib\SAX.lib" \
	"..\..\lib\Utilities.lib"

"$(OUTDIR)\SimpleHandler.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SimpleHandler.dep")
!INCLUDE "SimpleHandler.dep"
!ELSE 
!MESSAGE Warning: cannot find "SimpleHandler.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SimpleHandler - Win32 Release" || "$(CFG)" == "SimpleHandler - Win32 Debug"
SOURCE=.\SimpleHandler.cpp

!IF  "$(CFG)" == "SimpleHandler - Win32 Release"


"$(INTDIR)\SimpleHandler.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SimpleHandler - Win32 Debug"


"$(INTDIR)\SimpleHandler.obj"	"$(INTDIR)\SimpleHandler.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\wrapper.cpp

!IF  "$(CFG)" == "SimpleHandler - Win32 Release"


"$(INTDIR)\wrapper.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SimpleHandler - Win32 Debug"


"$(INTDIR)\wrapper.obj"	"$(INTDIR)\wrapper.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "SimpleHandler - Win32 Release"

"SAXlib - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" 
   cd "..\examples\SAX"

"SAXlib - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ELSEIF  "$(CFG)" == "SimpleHandler - Win32 Debug"

"SAXlib - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" 
   cd "..\examples\SAX"

"SAXlib - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="SAXlib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ENDIF 

!IF  "$(CFG)" == "SimpleHandler - Win32 Release"

"Utilities - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\Utils"
   $(MAKE) /$(MAKEFLAGS) /F .\Utilities.mak CFG="Utilities - Win32 Release" 
   cd "..\examples\SAX"

"Utilities - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\Utils"
   $(MAKE) /$(MAKEFLAGS) /F .\Utilities.mak CFG="Utilities - Win32 Release" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ELSEIF  "$(CFG)" == "SimpleHandler - Win32 Debug"

"Utilities - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\Utils"
   $(MAKE) /$(MAKEFLAGS) /F .\Utilities.mak CFG="Utilities - Win32 Debug" 
   cd "..\examples\SAX"

"Utilities - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\Utils"
   $(MAKE) /$(MAKEFLAGS) /F .\Utilities.mak CFG="Utilities - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ENDIF 


!ENDIF 

