# Microsoft Developer Studio Generated NMAKE File, Based on SimpleHandler.dsp
!IF "$(CFG)" == ""
CFG=example_SAXSimpleHandler - Win32 Debug
!MESSAGE No configuration specified. Defaulting to example_SAXSimpleHandler - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "example_SAXSimpleHandler - Win32 Release" && "$(CFG)" != "example_SAXSimpleHandler - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleHandler.mak" CFG="example_SAXSimpleHandler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "example_SAXSimpleHandler - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "example_SAXSimpleHandler - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Release"

OUTDIR=.\..\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleHandler.exe"

!ELSE 

ALL : "ArabicaLib - Win32 Release" "$(OUTDIR)\SimpleHandler.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ArabicaLib - Win32 ReleaseCLEAN" 
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

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleHandler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SimpleHandler.pdb" /machine:I386 /out:"$(OUTDIR)\SimpleHandler.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SimpleHandler.obj" \
	"$(INTDIR)\wrapper.obj" \
	"..\..\lib\Arabica.lib"

"$(OUTDIR)\SimpleHandler.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Debug"

OUTDIR=.\..\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleHandler.exe" "$(OUTDIR)\SimpleHandler.bsc"

!ELSE 

ALL : "ArabicaLib - Win32 Debug" "$(OUTDIR)\SimpleHandler.exe" "$(OUTDIR)\SimpleHandler.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ArabicaLib - Win32 DebugCLEAN" 
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

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
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
	"..\..\lib\Arabica.lib"

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


!IF "$(CFG)" == "example_SAXSimpleHandler - Win32 Release" || "$(CFG)" == "example_SAXSimpleHandler - Win32 Debug"
SOURCE=.\SimpleHandler.cpp

!IF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Release"


"$(INTDIR)\SimpleHandler.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Debug"


"$(INTDIR)\SimpleHandler.obj"	"$(INTDIR)\SimpleHandler.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\wrapper.cpp

!IF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Release"


"$(INTDIR)\wrapper.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Debug"


"$(INTDIR)\wrapper.obj"	"$(INTDIR)\wrapper.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Release"

"ArabicaLib - Win32 Release" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Release" 
   cd "..\examples\SAX"

"ArabicaLib - Win32 ReleaseCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ELSEIF  "$(CFG)" == "example_SAXSimpleHandler - Win32 Debug"

"ArabicaLib - Win32 Debug" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Debug" 
   cd "..\examples\SAX"

"ArabicaLib - Win32 DebugCLEAN" : 
   cd "\work\JezUK\Arabica\src\SAX"
   $(MAKE) /$(MAKEFLAGS) /F .\SAX.mak CFG="ArabicaLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\examples\SAX"

!ENDIF 


!ENDIF 

