<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace31 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test name functions on text nodes. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select=".//text()"/>
  </out>
</xsl:template>

<xsl:template match="text()">
  <xsl:text>
name|</xsl:text><xsl:value-of select="name()"/><xsl:text>|</xsl:text>
  <xsl:text>namespace-uri|</xsl:text><xsl:value-of select="namespace-uri()"/><xsl:text>|</xsl:text>
  <xsl:text>local-name|</xsl:text><xsl:value-of select="local-name()"/><xsl:text>|</xsl:text>
</xsl:template>

</xsl:stylesheet>
