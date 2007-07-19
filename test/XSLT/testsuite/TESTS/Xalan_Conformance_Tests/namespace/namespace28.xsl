<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace28 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Purpose: Test of local-name and name() on namespace axis. -->
  <!-- Creator: David Marston -->
  <!-- The local-name() function should work on this axis, returning the same value as name().
     The XML parser has freedom to present namespaces in any order it wants.
     The input should have only one namespace if you want consistent results across parsers. -->

<xsl:output method="xml" encoding="UTF-8" indent="no" />

<xsl:template match="doc">
  <out>
    <xsl:value-of select="local-name(namespace::*[1])"/>
    <xsl:text>=</xsl:text>
    <xsl:value-of select="local-name(namespace::*[1])"/>
  </out>
</xsl:template>

</xsl:stylesheet>