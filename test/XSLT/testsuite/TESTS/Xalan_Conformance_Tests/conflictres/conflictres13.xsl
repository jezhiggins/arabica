<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres13 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that two patterns containing * at one level are equal
     in priority, despite one * being deeper. -->
  <!-- should see 1 conflict warning -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a|b|e">
  <xsl:value-of select="name(.)"/><xsl:text>:</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="a/b/*">
  <xsl:value-of select="name(.)"/><xsl:text>-Wildcard-last,</xsl:text>
</xsl:template>

<xsl:template match="a/*/c">
  <xsl:value-of select="name(.)"/><xsl:text>-Wildcard-middle,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
