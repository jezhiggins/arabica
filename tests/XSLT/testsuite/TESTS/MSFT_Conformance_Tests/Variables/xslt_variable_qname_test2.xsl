<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="http://domain" exclude-result-prefixes="foo">
    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <!-- Test for bug 71091 -->

    <xsl:variable name="foo:bookstore" select="bookstore"/>

    <xsl:template match="/">
        <xsl:for-each select="$foo:bookstore/book">
	<hello/>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>