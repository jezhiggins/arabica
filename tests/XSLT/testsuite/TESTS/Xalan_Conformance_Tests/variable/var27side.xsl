<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: var27side -->
  <!-- Purpose: to be imported by variable27 -->

<xsl:param name="test" select="'test value set in var27side'"/>

<xsl:template match="b">
  <xsl:text>
  On the side: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>