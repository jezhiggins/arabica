<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="unknown">
	<!-- '...' is an invalid XPath Expression but is not evaluated because match is 'unknown'-->
	<xsl:value-of select="..."/>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>



