<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position102 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 -->
  <!-- Creator: David Marston, from an idea by Kai Ojansuu -->
  <!-- Purpose: Test position() when template is imported. -->

<xsl:import href="pos102imp.xsl"/>

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="a"/>
    <xsl:apply-templates select="b"/>
    <xsl:apply-templates select="c"/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:text>
</xsl:text>
  <local>
    <xsl:text>Item </xsl:text>
    <xsl:value-of select="@mark"/>
    <xsl:text> is in position </xsl:text>
    <xsl:value-of select="position()"/>
  </local>
</xsl:template>

<xsl:template match="c">
  <xsl:text>
</xsl:text>
  <apply level="main">
    <xsl:text>Item </xsl:text>
    <xsl:value-of select="@mark"/>
    <xsl:text> is in position </xsl:text>
    <xsl:value-of select="position()"/>
  </apply>
  <xsl:apply-imports/>
</xsl:template>

</xsl:stylesheet>
