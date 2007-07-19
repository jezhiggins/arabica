<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that second instance of template wins. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:text>First Match-of-wildcard</xsl:text>
</xsl:template>

<xsl:template match="*">
  <xsl:text>Second Match-of-wildcard</xsl:text>
</xsl:template>

</xsl:stylesheet>