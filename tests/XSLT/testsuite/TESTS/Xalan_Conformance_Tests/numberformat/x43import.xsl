<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 

  <!-- FileName: x43import -->
  <!-- Purpose: Imported by NumberFormat43 and 44 -->

<xsl:decimal-format name="decimal3" digit='#' NaN='not a number'/>

<xsl:template name="sub">
  <sub>
    <xsl:value-of select="format-number('NaN','###','decimal3')"/>
    <xsl:text>, </xsl:text>
    <xsl:value-of select="format-number(-13.2,'###.0','decimal3')"/>
  </sub>
</xsl:template>

</xsl:stylesheet>
