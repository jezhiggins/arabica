<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>

<!-- key(string, object) second param is a variable-->

<xsl:output method="html" omit-xml-declaration="yes" indent="yes">
</xsl:output>

<xsl:variable name="var1">German</xsl:variable>

<xsl:key name="a" use="./item/@made" match="//items" />

<xsl:template match="/">
    <xsl:for-each select="key('a', $var1 )" >
         <LI><xsl:copy-of select="."/>
         </LI>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
