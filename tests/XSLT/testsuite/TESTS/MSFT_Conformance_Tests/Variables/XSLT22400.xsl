<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="text()"></xsl:template>
    <xsl:template match="book">
        <xsl:for-each select="title">
            
******
            <xsl:value-of select="$x"></xsl:value-of>
            ******
            <xsl:value-of select="text()"></xsl:value-of>
        </xsl:for-each>
        <xsl:param name="x">Book</xsl:param>
    </xsl:template>
</xsl:stylesheet>
