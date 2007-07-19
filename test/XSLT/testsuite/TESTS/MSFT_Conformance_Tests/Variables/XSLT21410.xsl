<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
    <xsl:template match="/">
        <xsl:value-of select="$X"></xsl:value-of>
        <xsl:apply-templates select="bookstore/book"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        
$
        <xsl:value-of select="price"></xsl:value-of>
        <xsl:value-of select="title"></xsl:value-of>
    </xsl:template>
    <xsl:template match="magazine"></xsl:template>
    <xsl:template match="my:*"></xsl:template>
    <xsl:variable name="X">I am variable here me roar.</xsl:variable>
</xsl:stylesheet>
