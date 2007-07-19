<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:decimal-format
        name="foo"
        decimal-separator=","
        digit="*"
        grouping-separator="."
        minus-sign="_"
        pattern-separator=":"
        percent="C"
        per-mille="M"
        zero-digit="a"
        infinity="Biggest"
        NaN="Not A Number"/>

    <xsl:decimal-format name="xsl:format" digit="-"/>

	<xsl:template match="/">

        <test1><xsl:value-of select="format-number(-98.7, '*.aaa,a**C', 'foo')"/></test1>
        <test2><xsl:value-of select="format-number(-98.7, '*,*M:(*)', 'foo')"/></test2>
        <test3><xsl:value-of select="format-number(1.0 div 0.0, '*', 'foo')"/></test3>
        <test4><xsl:value-of select="format-number(-1.0 div 0.0, '*', 'foo')"/></test4>
        <test5><xsl:value-of select="format-number(0.0 div 0.0, '*', 'foo')"/></test5>

        <test1><xsl:value-of select="format-number(12.345, '#.##0,0#%')"/></test1>
        <test2><xsl:value-of select="format-number(1.0 div 0.0, '#.##0,0#%')"/></test2>
        <test3><xsl:value-of select="format-number(12.34, '---.--', concat('xsl:', 'format'))"/></test3>

	</xsl:template>

    <xsl:decimal-format decimal-separator="," grouping-separator="."/>
    <xsl:decimal-format/>

    <!-- Redefine foo, but with same values for attributes -->
    <xsl:decimal-format
        name="foo"
        decimal-separator=","
        grouping-separator="."
        pattern-separator=":"
        per-mille="M"
        infinity="Biggest"/>

</xsl:stylesheet>
