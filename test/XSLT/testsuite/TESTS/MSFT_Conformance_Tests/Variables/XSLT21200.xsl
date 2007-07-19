<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:variable name="x" select="bookstore/book/title"></xsl:variable>
    <xsl:template match="/">
        <xsl:for-each select="$x">
            
******
            <xsl:value-of select="."></xsl:value-of>
            ******
	
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
