<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<!-- -->
<!-- declare xsl:key as non-top level element -->
<xsl:key name="a" use="//term" match="article" />

<xsl:template match="/">
    <xsl:for-each select="key('a', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
        <HTML>
        </HTML>
    </xsl:for-each>
</xsl:template>

<xsl:variable name="abc" select="//*"> 
<xsl:key name="a" use="//term" match="article" />
</xsl:variable>

</xsl:stylesheet>
