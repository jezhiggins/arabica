<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:template match="/">
        <xsl:for-each select="//testcases/testcase/doublePeriod">
		<xsl:element name="test">
                <xsl:variable name="number" select="../@number"/>
                <xsl:variable name="pattern" select="."/>
				<xsl:value-of select="$number"/>***<xsl:value-of select="$pattern"/>***<xsl:value-of select="format-number($number, $pattern)"/>
		</xsl:element>
        </xsl:for-each>
	</xsl:template>

</xsl:stylesheet>

