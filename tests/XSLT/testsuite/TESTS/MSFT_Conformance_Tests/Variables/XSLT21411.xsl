<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
    <xsl:template match="/">
        <xsl:variable name="Y" select="1"></xsl:variable>
        <xsl:variable name="X" select="$Y"></xsl:variable>
        <xsl:apply-templates select="bookstore/book"></xsl:apply-templates>
        
Level 1: X=
        <xsl:value-of select="$X"></xsl:value-of>
    </xsl:template>
    <xsl:template match="book">
        <xsl:variable name="Y" select="2"></xsl:variable>
        <xsl:variable name="X" select="$Y"></xsl:variable>
        <xsl:apply-templates select="/bookstore/book/author/last-name"></xsl:apply-templates>
        
Level 2: X=
        <xsl:value-of select="$X"></xsl:value-of>
    </xsl:template>
    <xsl:template match="magazine"></xsl:template>
    <xsl:template match="my:*"></xsl:template>
    <xsl:template match="last-name">
        <xsl:variable name="Y" select="3"></xsl:variable>
        <xsl:variable name="X" select="$Y"></xsl:variable>
        
Level 3: X=
        <xsl:value-of select="$X"></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
