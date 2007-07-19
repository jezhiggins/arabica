<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select75 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.1 Root node -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Ensure that select='/' gets what it should. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="doc"/>
    <xsl:text>
</xsl:text>
  </out>
</xsl:template>

<xsl:template match="doc">
  <xsl:apply-templates select="comment()" mode="showcomments"/>
  <xsl:apply-templates select="inner"/>
</xsl:template>

<xsl:template match="inner">
  <xsl:apply-templates select="/" mode="showcomments"/>
</xsl:template>

<xsl:template match="/" mode="showcomments">
  <xsl:text>
...Back to top...</xsl:text>
  <xsl:apply-templates select="comment()" mode="showcomments"/>
</xsl:template>

<xsl:template match="comment()" mode="showcomments">
  <xsl:text>
Comment found:</xsl:text>
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
