<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="unknown">
	<!--the function system-property(string) is called with wrong number of arguments and is not evaluated-->
	<xsl:value-of select="system-property('xsl:version', 'foo:bar')"/>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>



