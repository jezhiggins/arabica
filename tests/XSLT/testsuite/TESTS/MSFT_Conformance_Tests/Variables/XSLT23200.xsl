<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="URI">
    <xsl:template match="/">
        <xsl:apply-templates select="bookstore/book">
            <xsl:with-param name="x">Hey</xsl:with-param>
        </xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        <xsl:param name="foo:x">Magazine</xsl:param>
        <xsl:param name="x">Magazine</xsl:param>
        <xsl:apply-templates select="title">
            <xsl:with-param name="x" select="title/text()"></xsl:with-param>
        </xsl:apply-templates>
    </xsl:template>
    <xsl:template match="title">
        <xsl:param name="x">Temp Value</xsl:param>
        
Title: "
        <xsl:value-of select="$x"></xsl:value-of>
        "

    </xsl:template>
</xsl:stylesheet>
