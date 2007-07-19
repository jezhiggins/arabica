<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="p">
        <DIV>
            <B>
                <xsl:text> copy-of : </xsl:text>
            </B>
            <xsl:copy-of select="."></xsl:copy-of>
        </DIV>
        <DIV>
            <B>
                <xsl:text> copy : </xsl:text>
            </B>
            <xsl:copy></xsl:copy>
        </DIV>
        <DIV>
            <B>
                <xsl:text> value-of : </xsl:text>
            </B>
            <xsl:value-of select="."></xsl:value-of>
        </DIV>
         
FOR EACH 

        <xsl:for-each select="*|text()">
            <xsl:copy></xsl:copy>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
