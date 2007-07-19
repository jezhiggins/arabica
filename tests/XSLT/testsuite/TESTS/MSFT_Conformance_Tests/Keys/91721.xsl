<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<!-- key('foo', 'bar') where 'foo' is not declare as xsl:key  -->

<xsl:key name="a" use="//term" match="article" />

<xsl:template match="/">
    <out>
    <xsl:for-each select="key('foo', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
    </xsl:for-each>
    </out>
</xsl:template>

<xsl:variable name="abc" select="//*"> 
</xsl:variable>

</xsl:stylesheet>
