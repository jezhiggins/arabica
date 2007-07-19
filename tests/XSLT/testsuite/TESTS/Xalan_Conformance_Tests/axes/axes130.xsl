<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes130 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for 'self::' axis on an attribute -->

<xsl:output method="xml" encoding="UTF-8" indent="yes" />

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="@*"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="@*">
  <xsl:choose>
    <xsl:when test="self::node()">
      <any-node>true</any-node>
    </xsl:when>
    <xsl:otherwise>
      <any-node>false</any-node>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:choose>
    <!-- FALSE: principal node type of self is element -->
    <xsl:when test="self::*">
      <any-elem>true</any-elem>
    </xsl:when>
    <xsl:otherwise>
      <any-elem>false</any-elem>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:choose>
    <xsl:when test="self::text()">
      <any-text>true</any-text>
    </xsl:when>
    <xsl:otherwise>
      <any-text>false</any-text>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:choose>
    <!-- FALSE: principal node type of self is element -->
    <xsl:when test="self::center-attr">
      <named>true</named>
    </xsl:when>
    <xsl:otherwise>
      <named>false</named>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>