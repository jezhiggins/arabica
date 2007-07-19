<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test of zero-digit in decimal-format. -->

<xsl:decimal-format zero-digit="a" />

<xsl:template match="/">
  <out>
    <xsl:value-of select="format-number(0123,'0000')"/>
  </out>
</xsl:template>

</xsl:stylesheet>
