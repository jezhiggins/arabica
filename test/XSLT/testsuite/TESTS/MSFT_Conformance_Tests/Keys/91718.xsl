<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes"/>

<!-- -->
<!-- invalid foo attribute in xsl:key -->

<xsl:key foo="bar" name="a" use="//term" match="article" />

<xsl:template match="/">
    <xsl:for-each select="key('a', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
