<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="doc1" priority="1.0">
	<xsl:for-each select="*">
		<xsl:value-of select="."/>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>