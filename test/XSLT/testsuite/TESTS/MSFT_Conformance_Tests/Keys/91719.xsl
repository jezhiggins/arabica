<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes"/>

<!-- -->
<!-- declare xsl:key in template -->

<xsl:key name="a" use="//term" match="article" />
<xsl:key name="a" use="//term" match="article" />

<xsl:template match="/">
    <xsl:key name="a" use="//term" match="article" />
    <xsl:for-each select="key('a', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
