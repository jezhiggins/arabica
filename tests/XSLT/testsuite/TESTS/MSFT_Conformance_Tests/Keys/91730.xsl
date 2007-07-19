<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

<!-- key(string, object) object is a nodeset -->

<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<xsl:key name="a" use="@made" match="//items/item" />

<xsl:template match="/">
    <xsl:for-each select="key('a', //query/item/@made )" >
         <LI><xsl:copy>
             <xsl:apply-templates select="@* | text()"/>
             </xsl:copy>
               
         </LI>
    </xsl:for-each>
</xsl:template>

<xsl:template match="@*">
    <xsl:copy/>
</xsl:template>

</xsl:stylesheet>
