<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: var29side -->
  <!-- Purpose: to be imported by variable29 -->

<xsl:param name="test" select="'set in var29side, should have highest precedence'"/>

<xsl:template match="a">
  <xsl:text>
  On the side: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="c">
  <xsl:text>
  Side again: </xsl:text><xsl:value-of select="$test"/>
</xsl:template>

</xsl:stylesheet>