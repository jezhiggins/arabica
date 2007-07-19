<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="bookstore/book">
        <xsl:apply-templates select="author"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="author" priority="1">
        
- 
        <SPAN style="color=green" ID="test">
            <xsl:value-of select="my:country"></xsl:value-of>
        </SPAN>
    </xsl:template>
    <xsl:template match="author" priority="-.5">
        
- 
        <SPAN style="color=red" ID="test">
            <xsl:value-of select="my:country"></xsl:value-of>
        </SPAN>
    </xsl:template>
</xsl:stylesheet>
