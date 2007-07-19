<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp26c -->
<!-- Purpose: Used indirectly by impincl26 -->

<xsl:import href="imp26d.xsl"/>

<!-- No template for outer or inner -->

<xsl:template match="middle">
  <C>
    <xsl:value-of select="name(.)"/>
    <xsl:text> Switching to inner...
</xsl:text>
    <xsl:apply-templates select="inner"/>
  </C>
</xsl:template>

</xsl:stylesheet>