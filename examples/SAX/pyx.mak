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

ALL : "$(OUTDIR)\pyx.exe"


CLEAN :
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
	"..\..\..\..\lib\vc6\expat.lib" \
	"..\..\lib\Utilities.lib"

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

ALL : "$(OUTDIR)\pyx.exe"


CLEAN :
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

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "..\..\\" /I "\work\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\pyx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pyx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\pyx.pdb" /debug /machine:I386 /out:"$(OUTDIR)\pyx.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\pyx.obj" \
	"..\..\lib\SAX.lib" \
	"..\..\..\..\lib\vc6\expat.lib" \
	"..\..\lib\Utilities.lib"

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



!ENDIF 

