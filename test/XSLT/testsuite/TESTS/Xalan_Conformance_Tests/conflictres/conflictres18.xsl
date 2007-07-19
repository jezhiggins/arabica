<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that @foo has higher priority than @*. -->
  <!-- should see no conflict warnings -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:text>a: </xsl:text>
  <xsl:apply-templates select="@*"/>
</xsl:template>

<xsl:template match="@*">
  <xsl:value-of select="name(.)"/><xsl:text>-Wildcard,</xsl:text>
</xsl:template>

<xsl:template match="@x1">
  <xsl:text>Found x1 attribute,</xsl:text>
</xsl:template>

</xsl:stylesheet>
