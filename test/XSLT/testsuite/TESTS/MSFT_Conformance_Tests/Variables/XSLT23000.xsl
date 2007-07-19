<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="URI">
    <xsl:template match="/">
        <xsl:apply-templates select="bookstore/book">
            <xsl:with-param>Book</xsl:with-param>
        </xsl:apply-templates>
    </xsl:template>
    <xsl:template match="book">
        <xsl:param name="foo:x">Magazine</xsl:param>
        <xsl:param name="x">Magazine</xsl:param>
        <xsl:value-of select="$foo:x"></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
