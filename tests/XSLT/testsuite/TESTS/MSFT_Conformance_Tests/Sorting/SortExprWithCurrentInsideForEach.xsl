<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" indent="yes" encoding="UTF-8"/>

	<xsl:template match="/">
		<xsl:for-each select="/collection/ref">
			<xsl:sort select="/collection/part[@id = current()/@refid]/@type"  order="ascending"/>
			
			<xsl:copy-of select="." />
			<xsl:copy-of select="/collection/part[@id = current()/@refid]" />
		</xsl:for-each>
	</xsl:template>

</xsl:stylesheet>
