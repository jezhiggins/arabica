<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="text"/>
    <xsl:output method="text" encoding="UTF-8"/>

    <!-- This shouldn't override the UTF-8 encoding -->
    <xsl:output method="text"/>

    <xsl:variable name="foo"><xsl:value-of select="/bookstore/book[1]/title"/><element/></xsl:variable>

	<xsl:template match="/">
        <xsl:comment>A comment</xsl:comment>
        <xsl:processing-instruction name="my-pi">A processing instruction</xsl:processing-instruction>
        Start

        <p>
            <xsl:attribute name="attr"><xsl:copy-of select="$foo"/>, Book 2</xsl:attribute>
            <p2>&lt;element&gt;&amp;amp;</p2>
            <p3><xsl:value-of select="bookstore/book[1]/title"/>&lt;/element&gt;</p3>
            <xsl:copy-of select="$foo"/>
        </p>
    </xsl:template>

</xsl:stylesheet>