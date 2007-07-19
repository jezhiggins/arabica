<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MODES04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.7 Modes -->
  <!-- Purpose: Simple test of xsl:apply-templates with no mode,
     but with same-pattern template that has a mode available. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="doc/a"/>
  </out>
</xsl:template>
  
<xsl:template match="a" mode="a">
  <xsl:text>mode-a:</xsl:text><xsl:value-of select="."/>
</xsl:template>

<xsl:template match="a">
  <xsl:text>no-mode:</xsl:text><xsl:value-of select="."/>
</xsl:template>
 
</xsl:stylesheet>
