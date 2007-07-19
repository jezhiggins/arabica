<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: var30mid -->
  <!-- Purpose: to be imported by variable30 -->

<xsl:import href="impfinal.xsl"/>

<xsl:param name="test" select="'value set in var30mid, should have highest precedence'"/>

<xsl:template match="b">
  <xsl:text>
  In middle: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>