<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres32 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: Tom Amiro -->
  <!-- Purpose: Test system allocated priorities for "@*[]". -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:text>a: </xsl:text>
  <xsl:apply-templates select="@*" />
</xsl:template>

<!-- should match because priority is 0.5 -->
<xsl:template match="@*[name()='x1']">
  <xsl:text>Correct - Matched "@*[name()='x1']"</xsl:text>
</xsl:template>

<!-- should not match because priority is 0 -->
<xsl:template match="@x1">
  <xsl:text>Matched "@x1"</xsl:text>
</xsl:template>

</xsl:stylesheet>