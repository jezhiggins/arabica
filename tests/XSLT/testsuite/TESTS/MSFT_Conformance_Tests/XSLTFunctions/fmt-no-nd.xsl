<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>
	<xsl:decimal-format name="european" decimal-separator=',' grouping-separator='.' />
	<xsl:decimal-format name="non_digit" zero-digit='a' minus-sign='~' digit='-'/>
	<xsl:decimal-format name="NaN_infinity" NaN='Not Applicable' infinity='Out of Range' />
	<xsl:decimal-format name="percent" percent='c' per-mille='m' />
	<xsl:decimal-format name="pattern" pattern-separator='!' />

	<xsl:variable name="decfmt">non_digit</xsl:variable>

	<xsl:template match="/">
        <xsl:for-each select="//testcases/testcase/non_digitPattern">
		<xsl:element name="test">
                <xsl:variable name="number" select="../@number"/>
                <xsl:variable name="pattern" select="."/>
				<xsl:value-of select="$number"/>***<xsl:value-of select="$pattern"/>***<xsl:value-of select="format-number($number, $pattern, $decfmt)"/>
		</xsl:element>
        </xsl:for-each>
		<xsl:element name="test">1 div 0***#***<xsl:value-of select="format-number(1 div 0, '-', $decfmt)" />
		</xsl:element>		
		<xsl:element name="test">-1 div 0***#***<xsl:value-of select="format-number(-1 div 0, '-', $decfmt)" />
		</xsl:element>		
	</xsl:template>

</xsl:stylesheet>

