<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:include href="fcp.xsl">
		<xsl:fallback><xsl:text>xsl:include is not supposed to be inside a template but since there is a fallback, this will be ignored</xsl:text></xsl:fallback>	
	</xsl:include>
</xsl:template>

<xsl:template match="text()"/>


</xsl:stylesheet>



