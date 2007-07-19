<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- FileName: imp26b -->
<!-- Purpose: Used indirectly by impincl26 -->

<xsl:import href="imp26c.xsl"/>

<!-- No template for middle or inner -->

<xsl:template match="outer">
  <B>
    <xsl:value-of select="name(.)"/>
    <xsl:apply-imports/>
  </B>
</xsl:template>

</xsl:stylesheet>