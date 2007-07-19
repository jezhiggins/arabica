<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="//SECTION">
        <xsl:choose>
            <xsl:when test="SUMMARY">
                <P>
                    <xsl:text> SUMMARY: </xsl:text>
                    <xsl:value-of select="SUMMARY"></xsl:value-of>
                </P>
            </xsl:when>
            <xsl:otherwise>
                <xsl:for-each select="DATA">
                    <P>
                        <xsl:text> DATA: </xsl:text>
                        <xsl:value-of select="."></xsl:value-of>
                    </P>
                </xsl:for-each>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
