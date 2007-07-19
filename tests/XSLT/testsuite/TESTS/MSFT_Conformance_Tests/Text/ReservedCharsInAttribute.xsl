<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
	<foo>
	    <xsl:attribute name="attr1">
	        <xsl:for-each select="EscapeChars">
        	    <xsl:apply-templates></xsl:apply-templates>
        	</xsl:for-each>
	    </xsl:attribute>
	</foo>
    </xsl:template>
    <xsl:template match="char">
        <xsl:value-of select="."/>
    </xsl:template>

    <xsl:template match="text()"/>

</xsl:stylesheet>
