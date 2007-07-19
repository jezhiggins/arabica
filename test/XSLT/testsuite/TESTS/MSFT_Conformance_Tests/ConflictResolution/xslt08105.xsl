<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*|comment()|processing-instruction()|node()">
        
	
- 
        <SPAN style="color=green">
            <xsl:value-of select="name()"></xsl:value-of>
        </SPAN>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*|comment()|processing-instruction()|node()" priority="-.61">
        
- 
        <SPAN style="color=red">
            <xsl:value-of select="name()"></xsl:value-of>
            : 
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*" priority="-.51">
 BUG
</xsl:template>
    <xsl:template match="node()" priority="-.51">
BUG
</xsl:template>
    <xsl:template match="comment()" priority="-.51">
BUG
</xsl:template>
    <xsl:template match="processing-instruction()" priority="-.51">
BUG
</xsl:template>

    <xsl:template match="text()"/>
</xsl:stylesheet>
