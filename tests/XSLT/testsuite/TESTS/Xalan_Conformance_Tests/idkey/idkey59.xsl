<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey59 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: Frank Weiss -->
  <!-- Purpose: Test xsl:key with union in "use" attribute. -->

<xsl:output method="xml" encoding="UTF-8" indent="yes"/>

<xsl:key name="key1" match="div" use="x | y | z"/>

<xsl:template match="/">
  <out>
    <h1>Coordinate 25 (4 hits, 3 sections):</h1>
    <xsl:for-each select="key('key1', 25)">
      <title>
        <xsl:value-of select="title"/>
      </title>
    </xsl:for-each>
    <h1>Coordinate 39 (1 hit):</h1>
    <xsl:for-each select="key('key1', 39)">
      <title>
        <xsl:value-of select="title"/>
      </title>
    </xsl:for-each>
    <h1>Coordinate 44 (2 hits, 2 sections):</h1>
    <xsl:for-each select="key('key1', 44)">
      <title>
        <xsl:value-of select="title"/>
      </title>
    </xsl:for-each>
    <h1>Coordinate 75 (2 hits, 2 sections):</h1>
    <xsl:for-each select="key('key1', 75)">
      <title>
        <xsl:value-of select="title"/>
      </title>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
