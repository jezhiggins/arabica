<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<!-- This stylesheet is a regression test case for bug 66613. -->

	<xsl:template match="/">
		<xsl:element name="test">
		    <xsl:value-of select="format-number(123456, '#0;')"/>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>

