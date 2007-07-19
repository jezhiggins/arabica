<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math101 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that mod has precedence over + and -. -->

<xsl:variable name="anum" select="10"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="48 mod 17 - 2 mod 9 + 13 mod 5"/><xsl:text>,</xsl:text>
    <xsl:value-of select="56 mod round(n5*2+1.444) - n6 mod 4 + 7 mod n4"/><xsl:text>,</xsl:text>
    <xsl:value-of select="(77 mod $anum + n5 mod 8) mod $anum"/>
  </out>
</xsl:template>

</xsl:stylesheet>
