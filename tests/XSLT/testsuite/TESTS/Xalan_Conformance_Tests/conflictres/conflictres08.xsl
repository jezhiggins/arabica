<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Purpose: Test for conflict resolution with 2 non-simple patterns ('/' and predicate) -->
  <!-- Creator: Paul Dick -->
  <!-- 1 conflict warning should be seen. -->
  <!-- Should say "Match of non-simple '[...]'" -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="foo"/>
  </out>
</xsl:template>

<xsl:template match="doc/foo">
  <xsl:text>Match-of-non-simple '/'</xsl:text>
</xsl:template>

<xsl:template match="foo[@test]">
  <xsl:text>Match-of-non-simple '[...]'</xsl:text>
</xsl:template>

<xsl:template match="foo">
  <xsl:text>Match-of-qualified-name</xsl:text>
</xsl:template>

<xsl:template match="*">
  <xsl:text>Match-of-wildcard</xsl:text>
</xsl:template>

<xsl:template match="node()">
  <xsl:text>Match-of-node-type</xsl:text>
</xsl:template>

</xsl:stylesheet>
