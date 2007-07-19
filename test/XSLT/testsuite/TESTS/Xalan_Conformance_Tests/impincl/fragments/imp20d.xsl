<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp20d -->
<!-- Purpose: Used by impincl20 -->

<xsl:template match="/">
  <xsl:text>WRONG Match on / in imp20d.xsl&#xa;</xsl:text>
  <xsl:apply-templates select="foo"/>
</xsl:template>

<xsl:template match="foo">
  <D>
    <xsl:apply-imports/><!-- no imports here, so it will revert to built-ins -->
  </D>
</xsl:template>

<xsl:template match="bar">
  <xsl:text>match on bar in imp20d.xsl</xsl:text>
</xsl:template>

</xsl:stylesheet>
