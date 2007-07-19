<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
		<xsl:for-each select="//p">
			<xsl:value-of select="."/>
			<xsl:value-of disable-output-escaping="yes" select="."/>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
