<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:java="http://xml.apache.org/xslt/java"
	xmlns:ped="http://tester.com"
	xmlns:jad="http://administrator.com"
	xmlns="http://www.lotus.com"
      exclude-result-prefixes="java jad #default">

  <!-- FileName: lre02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements-->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test exclusion of prefixes specified as xsl:stylesheet attribute. -->
  <!-- Elaboration: The created element node will also have a copy of the namespace nodes 
       that were present on the element node in the stylesheet tree with the exception 
       of any namespace node whose string-value is the XSLT namespace URI, a namespace 
       URI declared as an extension namespace, or a namespace URI designated as an 
       excluded namespace. (Can't exclude namespaces that are used, however.)
    The default namespace is used, and so can't be excluded. -->

<xsl:template match="doc">
  <out english="to leave"/>
</xsl:template>

</xsl:stylesheet>