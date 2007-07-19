<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<!-- key(' a','blar') invalid name as first argv -->

<xsl:key name="a" use="term" match="//p" />

<xsl:template match="/">
    <xsl:for-each select="key(' a', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
    </xsl:for-each>
</xsl:template>

<xsl:variable name="abc" select="//*"> 
</xsl:variable>

</xsl:stylesheet>
