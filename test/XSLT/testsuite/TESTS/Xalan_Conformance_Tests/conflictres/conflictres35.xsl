<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres35 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that pattern a//b is equal priority than a/b, even though
     it allows more nodes to qualify. -->
  <!-- should see 2 conflict warnings -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a|c|d|e">
  <xsl:value-of select="name(.)"/><xsl:text>:</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="a//b">
  <xsl:value-of select="name(.)"/><xsl:text>-Descendant,</xsl:text>
</xsl:template>

<xsl:template match="a/b">
  <xsl:value-of select="name(.)"/><xsl:text>-Child,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
