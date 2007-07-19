<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:http="http://xyz"
  exclude-result-prefixes="http">

  <!-- FileName: attribvaltemplate12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use of colon in AVT expression to signify namespaced element. -->

<xsl:template match="doc">
  <out href="{http:val}"/>
</xsl:template>

</xsl:stylesheet>