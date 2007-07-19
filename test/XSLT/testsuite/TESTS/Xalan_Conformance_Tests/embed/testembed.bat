@ECHO OFF
set JAVAPROG=java
set savedCLASSPATH=%CLASSPATH%
set LOTUSXSLDIR=d:\xslt\testsuite\classes\

rem +++ This file is used to run embed01, embed02, embed07, embed08(4x) and paramtest.  +++
rem +++ Set classpath based on the build you are testing +++
rem +++ This is for XALANJ build.
rem
rem set XCLASSPATH=%LOTUSXSLDIR%xerces.jar;%LOTUSXSLDIR%xalan.jar;d:\xslt\testsuite\conf\extend\;%LOTUSXSLDIR%js.jar;%LOTUSXSLDIR%bsf.jar;%LOTUSXSLDIR%bsfengines.jar;%CLASSPATH%
rem This is for LOTUSXSL build.
set XCLASSPATH=%LOTUSXSLDIR%xerces.jar;%LOTUSXSLDIR%lotusxsl.jar;%LOTUSXSLDIR%xalan.jar;d:\xslt\testsuite\conf\extend\;%LOTUSXSLDIR%js.jar;%LOTUSXSLDIR%bsf.jar;%LOTUSXSLDIR%bsfengines.jar;%CLASSPATH%

%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -in embed01.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -in embed02.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -in embed07.xml 
type blank.out

%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -MEDIA xxx -in embed08.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -MEDIA yyy -in embed08.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -MEDIA zzz -in embed08.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -MEDIA xyz -in embed08.xml 
type blank.out
%JAVAPROG% -Djava.compiler=NONE -classpath %XCLASSPATH% org.apache.xalan.xslt.Process %2 %3 %4 %5 %6 -v -param pv1 'aa' -param pv2 'bb' -param pv3 'cc' -param pv4 'dd' -param pv5 'ee' -param pv6 'ff' -in paramtest.xml -xsl paramtest.xsl 
