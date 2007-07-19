<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:include href="lowpribooks17.xsl"></xsl:include>
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book[(title | @style) | price = 'textbook'] | book/title" priority="0.6">
        
- 
        <SPAN name="{name()}">
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book" priority="0.5">
        
- 
        <SPAN style="color=red-book">
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book/title" priority="0.5">
        
- 
        <SPAN style="color=green-title">
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
