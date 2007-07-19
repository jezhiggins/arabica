<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MDOCS05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test document() function with path following. -->

<xsl:template match="catalog">
  <out>
    <xsl:apply-templates select="document(pointer/urlref/@urlstr)/market.participant/business.identity.group/business.name"/>
    <xsl:apply-templates select="document('../mdocs/compu.xml')/market.participant/address.set/*"/>
  </out>
</xsl:template>

<xsl:template match="location.in.street">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="street">
  <xsl:apply-templates/><xsl:text></xsl:text>
</xsl:template>

<xsl:template match="city">
  <xsl:apply-templates/><xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="country.subentity">
  <xsl:apply-templates/><xsl:text> </xsl:text>
</xsl:template>

<xsl:template match="postcode">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="telephone.number">
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
