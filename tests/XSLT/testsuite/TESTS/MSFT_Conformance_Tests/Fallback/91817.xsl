<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="title">

		<xsl:fallback>
			<xsl:value-of select="text()"/>
		</xsl:fallback>

</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>