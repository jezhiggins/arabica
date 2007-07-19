<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="10000b.xsl"/>
	<xsl:template name="a10000">
		<xsl:value-of select="'Hello from 10000a'"/>,
		<xsl:call-template name="b10000"/> 
	</xsl:template>
</xsl:stylesheet>
