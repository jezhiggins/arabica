<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">

	<xsl:foo>
		<xsl:fallback>
			<xsl:text>xsl:foo is not available in XSLT 1.0 and there is a fallback, so process the content of the fallback element
		</xsl:text>
		</xsl:fallback>
	</xsl:foo>

</xsl:template>


</xsl:stylesheet>



