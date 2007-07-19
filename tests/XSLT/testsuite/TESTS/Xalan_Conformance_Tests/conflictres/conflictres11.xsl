<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres11 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for conflict resolution - two different node tests. -->
  <!-- should see 1 conflict warning -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="node()">
  <xsl:text>Match-of-node,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="text()">
  <xsl:text>Match-of-text,</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
