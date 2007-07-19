<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="doc/foo | doc/bar">
  <out>
    <xsl:variable name="RTF">
      <xsl:value-of select="a"/>
    </xsl:variable>
    <xsl:call-template name="ntmp1">
      <xsl:with-param name="pvar1" select="$RTF"/>
    </xsl:call-template>
  </out>
</xsl:template>

<xsl:template name="ntmp1">
  <xsl:param name="pvar1">pvar1 default data</xsl:param>
  <xsl:param name="pvar2">pvar2 default data</xsl:param>
  <xsl:value-of select="$pvar1"/><xsl:text>,</xsl:text>
  <xsl:value-of select="$pvar2"/>
</xsl:template>

</xsl:stylesheet>
