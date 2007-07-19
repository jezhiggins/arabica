<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: node20 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for 'parent::node()' in select. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="parent::node()" mode="upward"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="node()" mode="upward">
  <xsl:value-of select="name(.)"/><xsl:text>, </xsl:text>
  <xsl:apply-templates select="parent::node()" mode="upward"/>
</xsl:template>

<xsl:template match="/" mode="upward">
  <xsl:text>Root Node</xsl:text>
</xsl:template>

</xsl:stylesheet>