<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="bookstore/magazine/*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:value-of select="."></xsl:value-of>
         BUG
	
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="bookstore/magazine/*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="bookstore/magazine/*">
        <span style="color:orange">
            <xsl:value-of select="name()"></xsl:value-of>
        </span>
	:
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        BUG
	 
        <xsl:value-of select="."></xsl:value-of>
        <xsl:apply-templates select="*"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:apply-templates select="*"/>
    </xsl:template>

    <xsl:template match="text()"/>
</xsl:stylesheet>
