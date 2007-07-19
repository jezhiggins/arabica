<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <xsl:variable name="foo" select="$foo"/>

        <xsl:value-of select="$foo"/>
    </xsl:template>

    <!-- Global variable foo refers to global variable bar, but not using forward reference -->

    <xsl:variable name="bar" select="'global bar'"/>
    <xsl:variable name="foo">global foo: <xsl:value-of select="$bar"/></xsl:variable>

</xsl:stylesheet>
