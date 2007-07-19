<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impfinal -->
  <!-- Purpose: to be imported by impmid and others -->

<xsl:param name="test" select="'test value set in impfinal'"/>

<xsl:template match="/">
  <out><xsl:text>
  In final: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
  </out>
</xsl:template>

</xsl:stylesheet>