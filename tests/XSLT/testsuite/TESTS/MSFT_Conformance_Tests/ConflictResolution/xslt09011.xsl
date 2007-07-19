<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:include href="lowpribooks17.xsl"></xsl:include>
    <xsl:output method="html"/>
    <xsl:template match="/">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine|magazine/title|processing-instruction()" priority="0.6">
        
- 
        <br></br>
         Pri 0.6 - 
        <SPAN style="color=blue">
            <xsl:value-of select="name()"></xsl:value-of>
             :
        </SPAN>
        <SPAN style="color:blue">
            <xsl:value-of select="."></xsl:value-of>
        </SPAN>
        <br></br>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine" priority=".6">
        <br></br>
        PASS on Document Order TEST (<xsl:value-of select="title"/>)
  
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
