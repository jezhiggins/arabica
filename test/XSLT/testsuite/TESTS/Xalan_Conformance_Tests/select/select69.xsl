<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select69 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test whether null string as attribute value causes selection problem. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:value-of select="."/><xsl:text>-</xsl:text>
  <xsl:for-each select="attribute::*">
    <xsl:sort select="name(.)"/>
    <xsl:value-of select="."/><xsl:text>|</xsl:text>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
