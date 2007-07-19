<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.5 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for simple identity transformation with template match -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="@*|comment()|processing-instruction()|text()|*">
  <xsl:copy>
    <xsl:apply-templates select="@*|comment()|processing-instruction()|text()|*"/>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>