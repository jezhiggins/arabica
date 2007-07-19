<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:variable name="var" select="foo"/>

<xsl:template match="doc">
    <xsl:apply-templates select="."/>
</xsl:template>

<xsl:template match="$var">
  <xsl:text>Error</xsl:text>
  <bee><xsl:value-of select="."/></bee>
</xsl:template>

</xsl:stylesheet>
