<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impmid -->
  <!-- Purpose: to be imported by variable22, 27, etc. -->

<xsl:import href="impfinal.xsl"/>

<xsl:param name="test" select="'test value set in impmid'"/>

<xsl:template match="a">
  <xsl:text>
  In middle: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>