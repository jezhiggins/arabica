<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="chapter">
  <xsl:for-each select="note">
    Note <xsl:number format="1" value="position()" /> of <xsl:value-of select="count(/doc/chapter/note)"/>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
