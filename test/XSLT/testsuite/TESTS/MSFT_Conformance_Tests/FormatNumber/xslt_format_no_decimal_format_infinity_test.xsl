<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:decimal-format infinity="off-the-scale" />

<xsl:template match="/">
  <out>
    <xsl:value-of select="format-number(1 div 0,'000000000')"/>
  </out>
</xsl:template>

</xsl:stylesheet>