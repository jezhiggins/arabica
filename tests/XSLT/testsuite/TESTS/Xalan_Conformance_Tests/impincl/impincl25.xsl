<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: impincl25 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show apply-imports matching a template deeper into the import tree. -->

<xsl:import href="fragments/imp25b.xsl"/>

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match="/doc">
  <out>
    <xsl:text>Match on /doc in top xsl</xsl:text>
    <xsl:apply-imports/>
  </out>
</xsl:template>

<xsl:template match="bar">
  <xsl:text> - match on bar in top xsl</xsl:text>
</xsl:template>

</xsl:stylesheet>