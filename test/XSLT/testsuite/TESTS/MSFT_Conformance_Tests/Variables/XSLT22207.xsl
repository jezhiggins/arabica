<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="http://www.HeyMan.com" xmlns:bar="httm://www.What.com">
    <xsl:param name="foo:x" select="bookstore/magazine/title"></xsl:param>
    <xsl:param name="foo:y" select="bookstore/book/title"></xsl:param>
    <xsl:param name="bar:x" select="bookstore/book/title"></xsl:param>
    <xsl:template match="/">
        <xsl:for-each select="$bar:x">
            
******
            <xsl:value-of select="node()"></xsl:value-of>
            ******
	
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
