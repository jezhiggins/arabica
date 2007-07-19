<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math100 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that div has precedence over + and -. -->

<xsl:variable name="anum" select="10"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="(24 div 3 +2) div (40 div 8 -3)"/><xsl:text>,</xsl:text>
    <xsl:value-of select="80 div n2 + 12 div 2 - n4 div n2"/><xsl:text>,</xsl:text>
    <xsl:value-of select="70 div $anum - 18 div n6 + $anum div n2"/>
  </out>
</xsl:template>

</xsl:stylesheet>
