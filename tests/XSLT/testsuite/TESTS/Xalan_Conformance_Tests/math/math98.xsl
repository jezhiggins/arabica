<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math98 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of repeated use of -. Space away from - when required. -->

<xsl:variable name="anum" select="10"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="100-9-7-4-17-18-5"/><xsl:text>,</xsl:text>
    <xsl:value-of select="100-n6 -4-n1 -1-11"/><xsl:text>,</xsl:text>
    <xsl:value-of select="100-$anum -5-15-$anum"/>
  </out>
</xsl:template>

</xsl:stylesheet>
