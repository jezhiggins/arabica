<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- FileName: c -->
<!-- Purpose: Used by impincl05, 06, 07, 12, 14 -->

<xsl:import href="e.xsl"/>

<xsl:template match="title">
  C-title: <xsl:value-of select="."/>
  <xsl:apply-imports/>
</xsl:template>

<xsl:template match="chapters">
  C-chapters: <xsl:apply-templates select="chapter"/>
  <xsl:text>&#10;</xsl:text>
</xsl:template>

</xsl:stylesheet>