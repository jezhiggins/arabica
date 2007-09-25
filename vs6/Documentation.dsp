# Microsoft Developer Studio Project File - Name="Documentation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=Documentation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Documentation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Documentation.mak" CFG="Documentation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Documentation - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "Documentation - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "Documentation - Win32 Release"

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

!ELSEIF  "$(CFG)" == "Documentation - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Documentation___Win32_Debug"
# PROP BASE Intermediate_Dir "Documentation___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Documentation___Win32_Debug"
# PROP Intermediate_Dir "Documentation___Win32_Debug"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Documentation - Win32 Release"
# Name "Documentation - Win32 Debug"
# Begin Group "doc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\doc\html\index.html
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\CONTRIBUTORS
# End Source File
# Begin Source File

SOURCE=.\LICENSE
# End Source File
# Begin Source File

SOURCE=.\sax.dox

!IF  "$(CFG)" == "Documentation - Win32 Release"

!ELSEIF  "$(CFG)" == "Documentation - Win32 Debug"

# Begin Custom Build - Building documentation
OutDir=.\Documentation___Win32_Debug
InputPath=.\sax.dox

"$(OutDir)\dummy" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	doxygen sax.dox

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Target
# End Project
