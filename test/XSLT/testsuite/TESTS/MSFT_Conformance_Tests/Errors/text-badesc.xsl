<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<!-- attribute values are case-sensitive, so this should fail -->
		<xsl:text disable-output-escaping="YES">Hello</xsl:text>
	</xsl:template>
</xsl:stylesheet>
