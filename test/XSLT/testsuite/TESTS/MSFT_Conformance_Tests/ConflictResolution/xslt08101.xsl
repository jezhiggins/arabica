<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
    <xsl:template match="/">
        <xsl:apply-templates select="//my:*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="my:book">
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="my:book" priority="-0.001">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
    </xsl:template>
    <xsl:template match="my:magazine" priority="0.001">
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="my:magazine">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
    </xsl:template>
    <xsl:template match="*" priority="-20">
        <span style="color:blue" name="{name()}">
            <xsl:apply-templates></xsl:apply-templates>
        </span>
    </xsl:template>
    <xsl:template match="text()" priority="-20">
        <span style="color:blue">
            <xsl:apply-templates></xsl:apply-templates>
        </span>
    </xsl:template>
</xsl:stylesheet>
