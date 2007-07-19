<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"  xsl:use-attribute-sets="foo">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo" >
	<xsl:attribute name="foo">foo</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="bookstore">
	<xsl:element name="elem" use-attribute-sets="foo bar">element</xsl:element>      
    </xsl:template>

    <xsl:attribute-set name="bar" >
	<xsl:attribute name="bar">bar</xsl:attribute>
    </xsl:attribute-set>

</xsl:stylesheet>

