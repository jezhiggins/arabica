<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string132 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of default (no functions) conversion of integers. -->

<xsl:template match="/">
  <out>
    <set>
    <xsl:text>Positive numbers:&#10;</xsl:text>
    <xsl:value-of select="1"/><xsl:text>,</xsl:text>
    <xsl:value-of select="12"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123"/><xsl:text>,</xsl:text>
    <xsl:value-of select="1234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="12345"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="1234567"/><xsl:text>,</xsl:text>
    <xsl:value-of select="12345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="1234567890"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="12345678901"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123456789012"/><xsl:text>,</xsl:text>
    <xsl:value-of select="1234567890123"/><xsl:text>,</xsl:text>
    <xsl:value-of select="12345678901234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123456789012345"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="1234567890123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="12345678901234567"/><xsl:text>,</xsl:text>
    <xsl:value-of select="123456789012345678"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:text>Negative numbers:&#10;</xsl:text>
    <xsl:value-of select="-1"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-12"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-1234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-12345"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-1234567"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-12345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-1234567890"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-12345678901"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123456789012"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-1234567890123"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-12345678901234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123456789012345"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-1234567890123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-12345678901234567"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-123456789012345678"/>
	</set>
  </out>
</xsl:template>

</xsl:stylesheet>
