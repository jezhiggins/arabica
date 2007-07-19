<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <!-- Foo refers many times to bar, including through intermediate.  No cycle should be reported -->
    <xsl:variable name="foo">
        <xsl:value-of select="$bar"/>
        <xsl:value-of select="$bar"/>
        <xsl:value-of select="$bar"/>
        <xsl:value-of select="$bar"/>
        <xsl:value-of select="$bar"/>
        <xsl:value-of select="$intermediate"/>
        <xsl:value-of select="$intermediate"/>
        <xsl:value-of select="$intermediate"/>
        <xsl:value-of select="$intermediate"/>
        <xsl:value-of select="$intermediate"/>
    </xsl:variable>

    <xsl:variable name="intermediate">
        <xsl:value-of select="$bar"/>
    </xsl:variable>

    <xsl:variable name="bar">
        <xsl:value-of select="'barval'"/>
    </xsl:variable>

    <xsl:template match="/">
        <xsl:copy-of select="$foo"/>
    </xsl:template>

</xsl:stylesheet>
