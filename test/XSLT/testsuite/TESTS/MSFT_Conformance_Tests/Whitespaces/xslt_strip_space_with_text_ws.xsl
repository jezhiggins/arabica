<?xml version='1.0'?>

<!-- This stylesheet is a test case for bug 70837. It validates that strip-space does not 
     strip text nodes along with whitespace -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output indent="yes" encoding="utf-8"/>

  <xsl:strip-space elements="*"/>

  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="text()">
    <root>
    <xsl:value-of select="."/>
    </root>
  </xsl:template>

</xsl:stylesheet>
