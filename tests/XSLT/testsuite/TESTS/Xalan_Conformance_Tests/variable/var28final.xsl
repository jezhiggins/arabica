<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: var28final -->
  <!-- Purpose: to be imported by var28mid -->

<xsl:param name="test" select="'test value set in final'"/>

<xsl:template match="b">
  <xsl:text>
  In final: </xsl:text><xsl:value-of select="$test"/>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>