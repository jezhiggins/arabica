<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres24 -->
  <!-- Scenario: Standard-XML -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Purpose: Test for conflict resolution on templates assigned equal priority. -->
  <!-- Creator: Gary Peskin -->
  <!-- should see 1 conflict warning, because both templates are at same priority, but
     the last one should be selected. If priorities weren't assigned, more specific one
     (the "a" template) would have won. -->

<xsl:strip-space elements="doc"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a" priority="-2.0">
  <xsl:text>This template should not be matched.</xsl:text>
</xsl:template>

<xsl:template match="node()" priority="-2.0">
  <xsl:text>This template should be matched.</xsl:text>
</xsl:template>

</xsl:stylesheet>
