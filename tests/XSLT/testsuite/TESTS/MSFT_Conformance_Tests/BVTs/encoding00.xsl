<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" encoding="iso-8859-1" omit-xml-declaration="yes" indent="yes" cdata-section-elements="cdata"/>

    <xsl:variable name="xml">
        <elt attr="" attr2="&#218;&#32000;" attr3="Surrogate &#100000; Char"/><xsl:text>&#10;</xsl:text>
        <cdata>&#218; This is &#32000; a test. &#100000;</cdata><xsl:text>&#10;</xsl:text>
        <xsl:text>&#218; This is &#32000; a test. &#100000;</xsl:text>
    </xsl:variable>

	<xsl:template match="/">

        <xsl:text>&#128;&#255;&#256;&#10;</xsl:text>
        <xsl:copy-of select="$xml"/><xsl:text>&#10;</xsl:text>
        <xsl:value-of select="concat('&lt;', string($xml), '&#10;&gt;')"/>
        <xsl:value-of disable-output-escaping="yes" select="concat('&#10;&lt;', string($xml), '&#10;&gt;')"/>
        <xsl:value-of select="concat('&#10;&lt;', string($xml), '&#10;&gt;&#10;')"/>
        <xsl:copy-of select="$xml"/>
        <xsl:text>&#10;&#128;&#255;&#256;</xsl:text>

	</xsl:template>

</xsl:stylesheet>
