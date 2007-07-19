<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres26 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: Santiago Pericas-Geertsen -->
  <!-- Purpose: Test explicit priorities vs. default for attributes. -->

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

<xsl:template match="@*" priority="0.1">
  <xsl:value-of select="name(.)"/><xsl:text>-Wildcard,</xsl:text>
</xsl:template>

<!-- Should not match as default priority is 0 -->
<xsl:template match="@x1">
  <xsl:text>Found x1 attribute,</xsl:text>
</xsl:template>

<!-- Should not match as default priority is 0 -->
<xsl:template match="@x2">
  <xsl:text>Found x2 attribute</xsl:text>
</xsl:template>

</xsl:stylesheet>