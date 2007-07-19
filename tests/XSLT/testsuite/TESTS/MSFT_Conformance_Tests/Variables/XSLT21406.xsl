<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:variable name="X">book</xsl:variable>
        <xsl:apply-templates select="bookstore/book" mode="$X"></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        <xsl:value-of select="title"></xsl:value-of>
        <xsl:value-of select="price"></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
