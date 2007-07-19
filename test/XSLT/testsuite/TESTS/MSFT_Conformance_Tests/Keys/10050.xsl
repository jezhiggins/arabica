<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:key name="foo" match="book" use="title"/>

    <xsl:template match="/">
        <xsl:apply-templates select="bookstore/book"/>
    </xsl:template>

    <xsl:template match="book">
        <xsl:variable name="title" select="title"/>
        <xsl:for-each select="key('foo', $title)">
	        <xsl:value-of select="position()"/>
	        <xsl:value-of select="last()"/>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
