<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href="decfmt2.xsl"/>
<xsl:decimal-format name="european" decimal-separator=',' grouping-separator='.' />
<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:template match="/">
		<xsl:element name="test">
                <xsl:variable name="number" select="12345.67"/>
                <xsl:variable name="pattern" select="'##.##0,0000'"/>
				<xsl:value-of select="$number"/>***<xsl:value-of select="$pattern"/>***<xsl:value-of select="format-number($number, $pattern)"/>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>

