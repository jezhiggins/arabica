<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:for-each select=".//@*">
            <xsl:value-of select="self::node()"></xsl:value-of>
            

        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
