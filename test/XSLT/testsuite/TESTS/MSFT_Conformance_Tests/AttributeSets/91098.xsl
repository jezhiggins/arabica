<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="bar">
	<xsl:attribute name="foo">foo</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="bookstore" xsl:use-attribute-sets="foo">
	<xsl:text xsl:use-attribute-sets="foo" >text</xsl:text>
<!-- bug#50251  case 91099.xsl
	<xsl:comment xsl:use-attribute-set="foo" use-attribute-sets="foo">text</xsl:comment>
-->
	<xsl:for-each select="book" xsl:use-attribute-sets="foo">
		<xsl:copy xsl:use-attribute-sets="foo"/>
		<xsl:value-of xsl:use-attribute-sets="foo" select="bar"/>
	</xsl:for-each>
	<xsl:apply-templates xsl:use-attribute-sets="foo" select="bar"/>
    </xsl:template>
	

</xsl:stylesheet>

