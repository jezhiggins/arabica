<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:variable name="X">Test Variable</xsl:variable>
    <xsl:template match="/">
        
***
        <xsl:value-of select="$X"></xsl:value-of>
        ***
	
    </xsl:template>
</xsl:stylesheet>
