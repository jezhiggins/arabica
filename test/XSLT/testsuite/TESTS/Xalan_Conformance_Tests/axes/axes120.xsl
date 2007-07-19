<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  				xmlns:a="http://name-a"
  				xmlns:b="http://name-b"
  				xmlns:c="http://namc-c">

  <!-- FileName: axes120 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 Axes-->
  <!-- Creator: Paul Dick (Revision of axes118) -->
  <!-- Purpose: Check that namespace nodes exist separately on each element. -->

<xsl:template match="/">
  <out>
    <xsl:text>&#010;</xsl:text>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a:root">
  <xsl:for-each select="self::node()|child::*"><xsl:text>&#010;</xsl:text>
    <xsl:element name="{name(.)}"/><xsl:text>&#010;</xsl:text>
  	<xsl:for-each select="namespace::*">
    	<xsl:sort select="name(.)"/><xsl:text>&#09;</xsl:text>
    	<xsl:element name="{name(.)}"><xsl:value-of select="."/></xsl:element><xsl:text>,&#010;</xsl:text>
  	</xsl:for-each>
  </xsl:for-each>
</xsl:template>

<xsl:template match="text()"/><!-- To suppress empty lines -->

</xsl:stylesheet>