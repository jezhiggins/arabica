<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
    <xsl:include href="lowpribooks17.xsl"></xsl:include>
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title|my:*" priority="0.25">
        
- 
        <SPAN style="color=brown">
            Pri .25 - 
            <xsl:value-of select="name()"></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title|my:magazine|processing-instruction()" priority="0.6">
        
- 
        <SPAN style="color=blue">
         Pri 0.6 - 
            <xsl:value-of select="name()"></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction">
BUG
</xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
