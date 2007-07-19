<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="http://www.HeyMan.com">
    <xsl:variable name="foo:x" select="bookstore/magazine/title"></xsl:variable>
    <xsl:variable name="foo:y" select="bookstore/book/title"></xsl:variable>
    <xsl:template match="/">
        <xsl:for-each select="$foo:y">
            
******
            <xsl:value-of select="node()"></xsl:value-of>
            ******
	
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
