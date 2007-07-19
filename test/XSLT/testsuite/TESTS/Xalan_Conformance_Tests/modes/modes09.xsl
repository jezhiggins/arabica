<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MODES09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test an apply-templates that has no select but has a mode. -->

<xsl:template match="letters">
  <out>
    <xsl:apply-templates mode="char"/>
  </out>
</xsl:template>

<xsl:template match="letter" mode="char">
  <xsl:text>-</xsl:text><xsl:value-of select="."/>
</xsl:template>

<xsl:template match="number" mode="char">
  <xsl:text>#</xsl:text><xsl:value-of select="."/>
</xsl:template>

<!-- The "punct" nodes in the input will get processed under the default
     template, in char mode, which copies the content. -->

<xsl:template match="letter">
  <xsl:text>We should not get this line!
</xsl:text>
</xsl:template>

</xsl:stylesheet>
