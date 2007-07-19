<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: var28mid -->
  <!-- Purpose: to be imported by variable28 -->

<xsl:import href="var28final.xsl"/>

<xsl:param name="test" select="'test value set in mid'"/>

<xsl:template match="/">
  <out><xsl:text>
  In middle: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
  </out>
</xsl:template>

</xsl:stylesheet>