<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:param name="bar" select="."/>
	<xsl:variable name="foo" select="/bookstore/book"/>

	<xsl:template match="/">
		<xsl:param name="bar" select="."/>
		<xsl:variable name="foo" select="bookstore"/>
		<xsl:value-of select=".//last-name"/>
	</xsl:template>
</xsl:stylesheet>
