<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:for-each select="EscapeChars">
            <xsl:apply-templates></xsl:apply-templates>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="char">
        <xsl:value-of select="." disable-output-escaping="yes"></xsl:value-of>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
