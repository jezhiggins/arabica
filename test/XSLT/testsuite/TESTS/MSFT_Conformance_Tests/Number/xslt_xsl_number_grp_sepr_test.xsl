<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Purpose: Test of excessive size of grouping-separator. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="note">
  <xsl:number level="any" from="chapter" format="(1) " grouping-size="2" grouping-separator="toobig" />
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
