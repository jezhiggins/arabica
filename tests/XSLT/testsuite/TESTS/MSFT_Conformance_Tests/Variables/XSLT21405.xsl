<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:variable name="Y" select="title"></xsl:variable>
        <xsl:apply-templates select="bookstore/book">
            <xsl:sort select="$Y"></xsl:sort>
        </xsl:apply-templates>
    </xsl:template>
    <xsl:template match="magazine"></xsl:template>
    <xsl:template match="book">
        <xsl:value-of select="title"></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
