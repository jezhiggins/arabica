<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres29 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test conflict of two ways to wildcard attributes. Also assign conflicting priority on a template. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:text>a: </xsl:text>
  <xsl:apply-templates select="@*"/>
</xsl:template>

<xsl:template match="@*">
  <xsl:value-of select="name(.)"/><xsl:text>-Star,</xsl:text>
</xsl:template>

<xsl:template match="attribute::node()">
  <xsl:value-of select="name(.)"/><xsl:text>-node(),</xsl:text>
</xsl:template>

<!-- below is same priority as previous 2 -->
<xsl:template match="@x2" priority="-0.5">
  <xsl:text>Found x2 attribute</xsl:text>
</xsl:template>

</xsl:stylesheet>