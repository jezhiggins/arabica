<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book" priority="-100">
        
- 
        <SPAN style="color=yellow">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book" priority="-200">
        
- 
        <SPAN style="color=yellow">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book|book/title" priority="-100">
        
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
    <xsl:template match="book" priority="-100">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book/title" priority="-100">
        
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
    <xsl:template match="magazine|magazine/title" priority="-100">
        
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
    <xsl:template match="magazine" priority="-100">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title" priority="-100">
        
- 
        <SPAN style="color=green">
            magazine 
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title" priority="-100">
        
- 
        <SPAN style="color=green">
            magazine 
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title" priority="-100">
        
- 
        <SPAN style="color=green">
            magazine 
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine/title" priority="-100">
        
- 
        <SPAN style="color=green">
            magazine 
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*" priority="-100">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="@*" priority="-100">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="//*" priority="-100">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()" priority="-100"></xsl:template>
    <xsl:template match="text()" priority="-100"></xsl:template>
</xsl:stylesheet>
