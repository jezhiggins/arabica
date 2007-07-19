<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="10001a.xsl"/>
<xsl:output method="text" omit-xml-declaration="yes"/>
	<xsl:template match="/">
		<xsl:value-of select="'Hello from 10001'"/>,
		<xsl:call-template name="a10001"/>
	</xsl:template>
</xsl:stylesheet>
