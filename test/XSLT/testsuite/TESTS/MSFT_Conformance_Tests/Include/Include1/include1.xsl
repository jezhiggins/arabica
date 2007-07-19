<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
    <xsl:include href="include2/include.xsl" />
    <xsl:template match="author" priority="0">
        
- 
        <SPAN style="color=green" ID="test">
            <xsl:value-of select="my:country"></xsl:value-of>
        </SPAN>
    </xsl:template>
    <xsl:include href="include.xsl" />
</xsl:stylesheet>
