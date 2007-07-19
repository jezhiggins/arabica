<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:decimal-format NaN="non-numeric" />

<xsl:template match="/">
  <out>
    <xsl:value-of select="format-number('foo','000000000')"/>
  </out>
</xsl:template>

</xsl:stylesheet>