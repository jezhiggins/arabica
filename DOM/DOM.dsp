# Microsoft Developer Studio Project File - Name="DOM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DOM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DOM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DOM.mak" CFG="DOM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DOM - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DOM - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DOM - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DOM - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "DOM - Win32 Release"
# Name "DOM - Win32 Debug"
# Begin Group "DOM"

# PROP Default_Filter ""
# Begin Group "Traversal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Traversal\DocumentTraversal.h
# End Source File
# Begin Source File

SOURCE=.\Traversal\NodeFilter.h
# End Source File
# Begin Source File

SOURCE=.\Traversal\NodeIterator.h
# End Source File
# Begin Source File

SOURCE=.\Traversal\TreeWalker.h
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Events\DocumentEvent.h
# End Source File
# Begin Source File

SOURCE=.\Events\Event.h
# End Source File
# Begin Source File

SOURCE=.\Events\EventException.h
# End Source File
# Begin Source File

SOURCE=.\Events\EventListener.h
# End Source File
# Begin Source File

SOURCE=.\Events\EventTarget.h
# End Source File
# Begin Source File

SOURCE=.\Events\MutationEvent.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Attr.h
# End Source File
# Begin Source File

SOURCE=.\CDATASection.h
# End Source File
# Begin Source File

SOURCE=.\CharacterData.h
# End Source File
# Begin Source File

SOURCE=.\Comment.h
# End Source File
# Begin Source File

SOURCE=.\Document.h
# End Source File
# Begin Source File

SOURCE=.\DocumentFragment.h
# End Source File
# Begin Source File

SOURCE=.\DocumentType.h
# End Source File
# Begin Source File

SOURCE=.\DOMException.h
# End Source File
# Begin Source File

SOURCE=.\DOMImplementation.h
# End Source File
# Begin Source File

SOURCE=.\Element.h
# End Source File
# Begin Source File

SOURCE=.\Entity.h
# End Source File
# Begin Source File

SOURCE=.\EntityReference.h
# End Source File
# Begin Source File

SOURCE=.\NamedNodeMap.h
# End Source File
# Begin Source File

SOURCE=.\Node.h
# End Source File
# Begin Source File

SOURCE=.\NodeList.h
# End Source File
# Begin Source File

SOURCE=.\Notation.h
# End Source File
# Begin Source File

SOURCE=.\ProcessingInstruction.h
# End Source File
# Begin Source File

SOURCE=.\Proxy.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# End Group
# Begin Group "Implementations"

# PROP Default_Filter ""
# Begin Group "Simple"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Simple\AttrImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\AttrMap.h
# End Source File
# Begin Source File

SOURCE=.\Simple\AttrNSImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\CDATASectionImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\CharacterDataImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\CommentImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\DocumentFragmentImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\DocumentImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\DocumentTypeImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\DOMImplementation.h
# End Source File
# Begin Source File

SOURCE=.\Simple\ElementByTagImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\ElementImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\ElementNSImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\EntityImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\EntityReferenceImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\Helpers.h
# End Source File
# Begin Source File

SOURCE=.\Simple\NamedNodeMapImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\NodeImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\NotationImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\ProcessingInstructionImpl.h
# End Source File
# Begin Source File

SOURCE=.\Simple\StringAdaptor.h
# End Source File
# Begin Source File

SOURCE=.\Simple\TextImpl.h
# End Source File
# End Group
# End Group
# End Target
# End Project
