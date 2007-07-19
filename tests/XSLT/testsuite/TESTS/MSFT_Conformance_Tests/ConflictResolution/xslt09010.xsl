<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:include href="lowpribooks17.xsl"></xsl:include>
    <xsl:output method="html"/>
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
    <xsl:template match="book|book/title|magazine/title" priority="0.25">
        
- 
        <SPAN style="color=brown">
            Pri .25 - 
            <xsl:element name="{name()}"><xsl:value-of select="*"/></xsl:element>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book/title">
        
- 
        <SPAN style="color=green">
            Default Pri .5 - 
            <xsl:element name="{name()}"><xsl:value-of select="."/></xsl:element>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine|magazine/title|book/price|processing-instruction()" priority="0.6">
        
- 
        <SPAN style="color=blue">
         Pri 0.6 - 
            <xsl:element name="{name()}"></xsl:element>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine">

BUG
  </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:include href="xslt09010lre.xsl"></xsl:include>
    <xsl:template match="processing-instruction">
BUG
</xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
