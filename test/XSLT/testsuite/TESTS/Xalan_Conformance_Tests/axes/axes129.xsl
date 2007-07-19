<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes129 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 Axes -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check the namespace axis starting from an attribute; should be empty -->

<xsl:output method="xml" encoding="UTF-8" indent="yes" />

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="doc">
    <xsl:apply-templates select="@*"/>
</xsl:template>

<xsl:template match="doc/@*">
  <ns-count attr="{name(.)}" count="{count(namespace::*)}"/>
</xsl:template>

<xsl:template match="text()"/><!-- To suppress empty lines -->

</xsl:stylesheet>