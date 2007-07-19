<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string133 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of default (no functions) conversion of decimal numbers with fractions. -->

<xsl:template match="/">
  <out>
   <set>
    <xsl:text>Positive numbers:&#10;</xsl:text>
    <xsl:value-of select=".1"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".01"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".012"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0123"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".01234"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".012345"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".01234567"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".012345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".10123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".101234567892"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".1012345678923"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".10123456789234"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".101234567892345"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".1012345678923456"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".10123456789234567"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".101234567892345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".1012345678923456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".10123456789234567893"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:text>Negative numbers:&#10;</xsl:text>
    <xsl:value-of select="-.1"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.01"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.012"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0123"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.01234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.012345"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0123456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.01234567"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.012345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.10123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.101234567892"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.1012345678923"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.10123456789234"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.101234567892345"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.1012345678923456"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.10123456789234567"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.101234567892345678"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.1012345678923456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.10123456789234567893"/><xsl:text>&#10;</xsl:text></set>
  </out>
</xsl:template>

</xsl:stylesheet>
