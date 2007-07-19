<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp21c -->
<!-- Purpose: Used indirectly by impincl21 and impincl25 -->

<xsl:template match="foo">
  <C>
    <xsl:value-of select="name(.)"/>
    <xsl:apply-templates select="bar"/>
  </C>
</xsl:template>

<xsl:template match="goo">
  <C>
    <xsl:value-of select="name(.)"/>
    <xsl:apply-templates select="bar"/>
  </C>
</xsl:template>

<xsl:template match="bar">
  <xsl:text> - match on bar in imp21c.xsl</xsl:text>
</xsl:template>

<xsl:template match="blob"><!-- no such node -->
  <xsl:apply-imports/>
</xsl:template>

</xsl:stylesheet>