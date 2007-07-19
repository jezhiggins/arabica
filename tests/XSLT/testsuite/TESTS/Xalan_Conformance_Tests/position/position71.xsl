<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position71 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that position test can be applied to PI nodes. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="./processing-instruction()[2]"/>	
  </out>
</xsl:template>

<xsl:template match="processing-instruction()">
  <xsl:text>Found PI: </xsl:text><xsl:value-of select="name()"/>
</xsl:template>

</xsl:stylesheet>
