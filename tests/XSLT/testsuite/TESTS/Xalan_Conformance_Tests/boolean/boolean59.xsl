<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean59 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test =, !=, and not, comparing node-set to string, where node-set is empty. -->

<xsl:template match="doc">
  <out>
    <xsl:variable name="x" select="avj//k"/><!-- empty -->
    <xsl:value-of select="$x='foo'"/>
    <xsl:value-of select="not($x='foo')"/><xsl:text> </xsl:text>
    <xsl:value-of select="$x!='foo'"/>
    <xsl:value-of select="not($x!='foo')"/>
  </out>
</xsl:template>

</xsl:stylesheet>