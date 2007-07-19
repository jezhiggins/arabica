<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that child and descendant are equal in priority. -->
  <!-- should see 2 conflict warnings -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a//b">
  <xsl:text>Descendant,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="a/b">
  <xsl:text>Child,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
