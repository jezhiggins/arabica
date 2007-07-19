<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp20b -->
<!-- Purpose: Used by impincl20 -->

<xsl:import href="imp20c.xsl"/>

<xsl:template match="/">
  <xsl:text>WRONG Match on / in imp20b.xsl&#xa;</xsl:text>
  <xsl:apply-templates select="foo"/>
</xsl:template>

<xsl:template match="foo">
  <B><xsl:apply-imports/></B>
</xsl:template>

<xsl:template match="bar">
  <xsl:text>match on bar in imp20b.xsl</xsl:text>
</xsl:template>

</xsl:stylesheet>
