<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">

	<xsl:foo>
		<xsl:text>xsl:foo is not available in XSLT 1.0 and there is no fallback, so error out </xsl:text>
	</xsl:foo>

</xsl:template>


</xsl:stylesheet>



