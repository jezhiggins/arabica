<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="10000a.xsl"/>
<xsl:output method="text" omit-xml-declaration="yes"/>
	<xsl:template match="/">
		<xsl:value-of select="'Hello from 10000'"/>,
		<xsl:call-template name="a10000"/>
	</xsl:template>
</xsl:stylesheet>
