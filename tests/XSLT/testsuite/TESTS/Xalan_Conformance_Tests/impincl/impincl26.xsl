<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: impincl26 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Each apply-imports must take its own view of the import tree. -->

<xsl:import href="fragments/imp26a.xsl"/>

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match="/doc">
  <out>
    <xsl:text>Match on /doc in top xsl</xsl:text>
    <xsl:apply-imports/>
  </out>
</xsl:template>

<xsl:template match="inner">
  <top>
    <xsl:value-of select="name(.)"/>
    <xsl:apply-imports/>
  </top>
</xsl:template>

</xsl:stylesheet>