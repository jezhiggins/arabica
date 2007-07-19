<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template match="/">
        <xsl:for-each select="foo">
            <p>
                <xsl:sort select="foo"/>
            </p>
        </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>
