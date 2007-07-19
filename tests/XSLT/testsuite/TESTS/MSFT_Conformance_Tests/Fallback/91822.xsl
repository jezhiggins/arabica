<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="book[@style='novel']">

<xsl:foo>	
    bar
	<xsl:fallback>
		<xsl:value-of select="$var"/>	
	</xsl:fallback>
</xsl:foo>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>