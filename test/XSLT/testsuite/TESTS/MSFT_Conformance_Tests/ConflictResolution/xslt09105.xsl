<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="bookstore" priority="0">
        <span style="color=red">
   first award in doc order </span>
        <p></p>
        <xsl:for-each select="book/author">
            <span>
                <xsl:value-of select="award"></xsl:value-of>
            </span>
            <br></br>
        </xsl:for-each>
        <span style="color:blue">
            <xsl:apply-templates></xsl:apply-templates>
        </span>
    </xsl:template>
    <xsl:template match="bookstore">
        <br></br>
        <span style="color=green">
   second award in doc order </span>
        <p></p>
        <xsl:for-each select="book/author">
            <span>
                <xsl:value-of select="award"></xsl:value-of>
            </span>
            <br></br>
        </xsl:for-each>
        <span style="color:blue">
            <xsl:apply-templates></xsl:apply-templates>
        </span>
    </xsl:template>
    <xsl:template match="/">
        <xsl:for-each select="//magazine/title">
            <br></br>
            <span style="color:red"> first title in doc order</span>
            <xsl:value-of select="."></xsl:value-of>
        </xsl:for-each>
        <span style="color:red">
            <xsl:apply-templates></xsl:apply-templates>
        </span>
    </xsl:template>
    <xsl:template match="/">
        <xsl:for-each select="//magazine/title">
            <br></br>
            <span style="color:green"> second title in doc order</span>
            <xsl:value-of select="."></xsl:value-of>
        </xsl:for-each>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*"></xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
