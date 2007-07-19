<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="utf-8" omit-xml-declaration="yes" indent="yes" cdata-section-elements="cdata"/>

    <xsl:variable name="surrogates">
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
        <xsl:text>&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;&#100000;</xsl:text>
    </xsl:variable>

	<xsl:template match="/">

        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:value-of select="$surrogates"/>
        <xsl:text>&#10;# surrogates: </xsl:text><xsl:value-of select="string-length(string($surrogates)) * 10"/><xsl:text>&#10;</xsl:text>

	</xsl:template>

</xsl:stylesheet>
