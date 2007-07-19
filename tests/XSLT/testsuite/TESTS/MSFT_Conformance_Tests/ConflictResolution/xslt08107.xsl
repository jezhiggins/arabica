<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="book">
        
	
- 
        <SPAN style="color=yellow">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="book|magazine">
        
	
- 
        <SPAN style="color=blue">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="book" priority="-.001">
        
	
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>
    <xsl:template match="magazine" priority=".1">
        
	
- 
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
             :
            <xsl:value-of select="title"></xsl:value-of>
        </SPAN>
        <br></br>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
