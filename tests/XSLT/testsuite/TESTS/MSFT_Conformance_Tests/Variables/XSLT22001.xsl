<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:foo="Test">
    <xsl:param name="foo:X">Test Variable</xsl:param>
    <xsl:template match="/">
        
***
        <xsl:value-of select="$foo:X"></xsl:value-of>
        ***
	
    </xsl:template>
</xsl:stylesheet>
