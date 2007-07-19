<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes"/>

<!-- xsl:key : use=" ", space in use expression-->

<xsl:key name="a" use=" "  match="article">
	<xsl:template match="/">
		<xsl:value-of select="text()"/>
	</xsl:template>
</xsl:key>

<xsl:template match="/">
    <xsl:for-each select="key('a', 'middle tier')" >
         <LI><xsl:value-of select="string(.)"/></LI>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
