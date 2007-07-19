<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: modes11 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.7 -->
  <!-- Creator: Carmelo Montanez --><!-- Template001 in NIST suite -->
  <!-- Purpose: Test apply-templates for a comment with a mode
       and moded matching template. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="comment()" mode="mode1"/>
  </out>
</xsl:template>

<xsl:template match="comment()" mode="mode1">
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="comment()">
  This test failed to execute properly.
</xsl:template>

</xsl:stylesheet>
