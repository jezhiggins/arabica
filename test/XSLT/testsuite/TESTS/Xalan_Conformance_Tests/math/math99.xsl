<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math99 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that * has precedence over + and -. -->

<xsl:variable name="anum" select="10"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="3*2+5*4-4*2-1"/><xsl:text>,</xsl:text>
    <xsl:value-of select="n6*5-8*n2+5*2"/><xsl:text>,</xsl:text>
    <xsl:value-of select="$anum*5-4*n2+n6*n1 -n3*3"/>
  </out>
</xsl:template>

</xsl:stylesheet>
