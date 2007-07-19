<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string135 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of default (no functions) conversion of small decimal numbers. -->

<xsl:template match="/">
  <out>
   <set>
    <xsl:text>Positive numbers:&#10;</xsl:text>
    <xsl:value-of select=".123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".00123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".00000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".00000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".0000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select=".000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".00000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".000000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select=".0000000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:text>Negative numbers:&#10;</xsl:text>
    <xsl:value-of select="-.123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.00123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.00000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.00000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000000000123456789"/><xsl:text>,</xsl:text>
    <xsl:value-of select="-.000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.00000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.000000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="-.0000000000000000000000000000000000000000123456789"/></set><set><xsl:text>&#10;</xsl:text>
  </set></out>
</xsl:template>

</xsl:stylesheet>
