<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:template match="/">
				<DIV><xsl:value-of select="format-number(-1234.5, '###0.00 ')"/></DIV>
				<DIV><xsl:value-of select="number('-1234.50 ')"/></DIV>
				<DIV><xsl:value-of select="number(format-number(-1234.5, '###0.00 '))"/></DIV>
	</xsl:template>
</xsl:stylesheet>

