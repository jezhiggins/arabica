<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp26a -->
<!-- Purpose: Used by impincl26 -->

<xsl:import href="imp26b.xsl"/>

<!-- No template for outer or inner -->

<xsl:template match="middle">
  <A>
    <xsl:value-of select="name(.)"/>
    <xsl:apply-imports/>
  </A>
</xsl:template>

</xsl:stylesheet>