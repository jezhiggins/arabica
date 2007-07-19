<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<!--the function system-property(string) is called with wrong type of argument is evaluated, so error out-->
	<xsl:value-of select="system-property(123)"/>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>



