<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:for-each select="//photo">
		<xsl:element name="{name()}">foo!</xsl:element>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>