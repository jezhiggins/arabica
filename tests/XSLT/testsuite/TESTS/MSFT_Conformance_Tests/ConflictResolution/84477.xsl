<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction() | book | book/title">
        
- 
        <SPAN style="color=yellow">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction() | book | book/title">
        
- 
        <SPAN style="color=brown">
            <xsl:value-of select="name()"></xsl:value-of>
             :
        </SPAN>
        <SPAN style="color:blue">
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction() | book/title">
        
- 
        <SPAN style="color=green">
            
book 
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction() | magazine | magazine/title">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="processing-instruction() | magazine |magazine/title">
        
- 
        <SPAN style="color=brown">
            <xsl:value-of select="name()"></xsl:value-of>
             :
        </SPAN>
        <SPAN style="color:blue">
            <xsl:value-of select="*"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
