<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:variable name="decfmt"></xsl:variable>

	<xsl:template match="/">
		<xsl:value-of select="format-number(12345, '#', $decfmt)" />
	</xsl:template>

</xsl:stylesheet>

