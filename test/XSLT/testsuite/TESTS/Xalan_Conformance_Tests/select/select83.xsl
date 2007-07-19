<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select83 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test //@x to get all attributes of a certain name -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="/doc/b/bb/bbb" />
  </out>
</xsl:template>

<xsl:template match="bbb">
  <list><xsl:apply-templates select="//@x"/></list>
</xsl:template>

<xsl:template match="@x">
  <xsl:text>
Node </xsl:text>
  <xsl:value-of select="name(..)" />
  <xsl:text> has </xsl:text>
  <xsl:value-of select="." />
  <xsl:text> in @x</xsl:text>
</xsl:template>

</xsl:stylesheet>