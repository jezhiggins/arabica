<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres16 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for conflict resolution on a predicate of a wildcard -->
  <!-- No conflict warnings should be seen. -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="file"/>
  </out>
</xsl:template>

<xsl:template match="*[@test='false']">
  <xsl:text>Match-predicated-wildcard,</xsl:text>
</xsl:template>

<xsl:template match="*">
  <xsl:text>Match-wildcard,</xsl:text>
</xsl:template>

</xsl:stylesheet>
