<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:param name="X">Test Variable</xsl:param>
    <xsl:template match="/">
        
***
        <xsl:value-of select="$X"></xsl:value-of>
        ***
	
    </xsl:template>
</xsl:stylesheet>
