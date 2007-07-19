<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MODES08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.7 Modes -->
  <!-- Purpose: Test of several modes being available. -->

<xsl:template match="doc">
  <out><xsl:text>&#010;</xsl:text>
    <xsl:apply-templates select="a" mode="a"/>
    <xsl:apply-templates select="a" mode="b"/>
    <xsl:apply-templates select="a" mode="c"/>
    <xsl:apply-templates select="a" mode="d"/>
    <xsl:apply-templates select="a" mode="e"/>
    <xsl:apply-templates select="b" mode="a"/>
    <xsl:apply-templates select="b" mode="b"/>
  </out>
</xsl:template>

<xsl:template match="a" mode="a">
  <xsl:text>modeA: </xsl:text><xsl:value-of select="."/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="a" mode="b">
  <xsl:text>modeB: </xsl:text><xsl:value-of select="."/>
  <xsl:value-of select="@test"/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="a" mode="c">
  <xsl:text>modeC: </xsl:text><xsl:value-of select="."/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="a" mode="d">
  <xsl:text>modeD: </xsl:text><xsl:value-of select="."/>
  <xsl:value-of select="@test"/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="a" mode="e">
  <xsl:text>modeE: </xsl:text><xsl:value-of select="."/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="*" mode="a">
  <xsl:text>modeA: </xsl:text><xsl:value-of select="."/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

<xsl:template match="*" mode="b">
  <xsl:text>modeB: </xsl:text><xsl:value-of select="."/>
  <xsl:text>&#010;</xsl:text>
</xsl:template>

</xsl:stylesheet>