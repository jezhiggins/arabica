<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        
- 
        <SPAN style="color=yellow">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book|book/title">
        
- 
        <SPAN style="color=brown">
            <xsl:value-of select="name()"></xsl:value-of>
             :
        </SPAN>
        <SPAN style="color:blue">
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book" priority="0.01">
        
- 
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book/title" priority=".49">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
