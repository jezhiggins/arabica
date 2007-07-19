<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:decimal-format name="foo" decimal-separator="," grouping-separator="." />

    <xsl:template match="/">
        <xsl:value-of select="format-number(1234.4321, '###.###,###', 'foo')"/>
    </xsl:template>

</xsl:stylesheet>