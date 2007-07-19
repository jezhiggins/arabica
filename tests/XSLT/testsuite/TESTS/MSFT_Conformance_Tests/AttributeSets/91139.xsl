<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="no" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="attr">123</xsl:attribute>
    </xsl:attribute-set>


    <xsl:attribute-set name="foo" >
        <xsl:attribute name="{$x}">XYZ</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
    	<foo xsl:use-attribute-sets="foo"/>
	<xsl:variable name="x">xxx</xsl:variable>
    </xsl:template>
</xsl:stylesheet>
