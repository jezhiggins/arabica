<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres27 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: Santiago Pericas-Geertsen -->
  <!-- Purpose: Test explicit priorities for "*". -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:text>a: </xsl:text>
</xsl:template>

<xsl:template match="*" priority="0.1">
  <xsl:text>Matched * on </xsl:text>
  <xsl:value-of select="name(.)"/>
  <xsl:text>;&#10;</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>