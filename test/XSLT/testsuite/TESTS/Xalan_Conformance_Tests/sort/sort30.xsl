<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="text"/>

  <!-- FileName: sort30 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for xsl:sort using a local variable in the select, apply-templates. -->

<xsl:template match="/">
  <xsl:variable name="index" select="1"/>
  <xsl:apply-templates select="doc/alpha">
    <xsl:sort select="*[$index]" data-type="text" />
  </xsl:apply-templates>
</xsl:template>

<xsl:template match="doc/alpha">
  <xsl:value-of select="display"/><xsl:text>,</xsl:text>
</xsl:template>

</xsl:stylesheet>