<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:decimal-format name='default' decimal-separator='!' grouping-separator='.' digit='#' />
	<xsl:variable name="x"/>
	<xsl:template match="/">
		<xsl:element name="test">
			<xsl:value-of select="format-number(x)"/>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>

