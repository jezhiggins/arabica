<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: node10 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for value-of with processing-instruction() node test. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="./processing-instruction()"/>	
  </out>
</xsl:template>

<xsl:template match="processing-instruction()">
  <xsl:text>Found-pi...</xsl:text>
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
