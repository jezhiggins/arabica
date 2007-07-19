<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math97 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of repeated use of +. -->

<xsl:variable name="anum" select="10"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="10+5+25+20+15+50+35+40"/><xsl:text>,</xsl:text>
    <xsl:value-of select="2+n5+7+n3"/><xsl:text>,</xsl:text>
    <xsl:value-of select="n2+3+$anum+7+n5"/>
  </out>
</xsl:template>

</xsl:stylesheet>
