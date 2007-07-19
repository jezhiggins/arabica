<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo" >
	<xsl:processing-instruction name="pi">foo</xsl:processing-instruction>
    </xsl:attribute-set>

    <xsl:template match="/">
	<literal xsl:use-attribute-sets="foo"/>
    </xsl:template>

    <xsl:attribute-set name="bar">
	<xsl:processing-instruction name="pi">foo</xsl:processing-instruction>
    </xsl:attribute-set>
</xsl:stylesheet>

