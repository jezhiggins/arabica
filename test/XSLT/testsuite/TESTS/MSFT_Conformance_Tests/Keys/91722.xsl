<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<!-- key() with no argument  -->

<xsl:key name="a" use="//fooblue" match="barblow" />

<xsl:template match="/">
    <xsl:for-each select="key()" >
         <LI><xsl:value-of select="string(.)"/></LI>
        <HTML>
        </HTML>
    </xsl:for-each>
</xsl:template>

<xsl:variable name="abc" select="//*"> 
</xsl:variable>

</xsl:stylesheet>
