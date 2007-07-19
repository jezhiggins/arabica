<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:template match="/">
				<DIV><xsl:value-of select="format-number(round(-.5), '#,##0.00')"/></DIV>
	</xsl:template>
</xsl:stylesheet>

