<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:include href="lowpribooks17.xsl"></xsl:include>
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine" priority="-.1">
        <br></br>
        FAIL on Document Order TEST
  
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:include href="xslt09009a.xsl"></xsl:include>
    <xsl:template match="processing-instruction">
BUG
</xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
