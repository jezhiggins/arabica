<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book[@style='textbook']">
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="book[@style='textbook']" priority=".49">
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="magazine[@style='glossy']">
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="magazine[@style='glossy']" priority=".51">
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="*" priority="-20">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()" priority="-20"/>
</xsl:stylesheet>
