<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable40 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Test top-level xsl:variable set using apply-templates -->
  <!-- Author: David Marston -->

<xsl:variable name="TreeFrag">
  <xsl:apply-templates select="//b" />
</xsl:variable>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="$TreeFrag"/><xsl:text>,</xsl:text>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a|d">
  <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="b">
  <xsl:apply-templates/><!-- expect only text, not child elements -->
</xsl:template>

<xsl:template match="c">
  <xsl:text>-</xsl:text><xsl:value-of select="."/><xsl:text>;</xsl:text>
</xsl:template>

</xsl:stylesheet>