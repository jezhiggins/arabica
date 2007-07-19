<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for conflict resolution on a predicate of a node test for comments. -->
  <!-- should see 1 conflict warning -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="comment()">
  <xsl:text>Any-comment,</xsl:text>
</xsl:template>

<xsl:template match="comment()[.=' a-comment ']">
  <xsl:text>Specific-comment,</xsl:text>
</xsl:template>

</xsl:stylesheet>
