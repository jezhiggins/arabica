<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<!-- key(string, object) where string is a param -->

<xsl:variable name="x" >a</xsl:variable>
<xsl:variable name="y" >b</xsl:variable>
<xsl:param name="z">$x</xsl:param>
<xsl:key name="ab" use="term" match="//p" />

<xsl:template match="/">
    <xsl:for-each select="key(concat($x,$y), 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
         <LI><xsl:value-of select="$x"/></LI>
         <LI><xsl:value-of select="$y"/></LI>
         <LI><xsl:value-of select="concat($x, $y)"/></LI>
    </xsl:for-each>
</xsl:template>

<xsl:variable name="abc" select="//*"> 
</xsl:variable>

</xsl:stylesheet>
