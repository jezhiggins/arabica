<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: modes12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.7 -->
  <!-- Creator: Carmelo Montanez --><!-- Template002 in NIST suite -->
  <!-- Purpose: Test apply-templates for PI with a mode
       and moded matching template. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="processing-instruction()" mode="mode1"/>
  </out>
</xsl:template>

<xsl:template match="processing-instruction()" mode="mode1">
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="processing-instruction()">
  This test failed to execute properly.
</xsl:template>

</xsl:stylesheet>
