<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match="/">
		<xsl:comment>foo &#x02D;- bar</xsl:comment>
	</xsl:template>

</xsl:stylesheet>