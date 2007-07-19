<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:include href="10001b.xsl"/>
	<xsl:template name="a10001">
		<xsl:value-of select="'Hello from 10001a'"/>,
		<xsl:call-template name="b10001"/> 
	</xsl:template>
</xsl:stylesheet>
