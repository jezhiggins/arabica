<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo" >
	<xsl:attribute name="foo">
		<xsl:copy use-attribute-sets="foo" />
		<xsl:value-of select="'testing'"/>
	</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="bookstore">
	<xsl:element name="elem" use-attribute-sets="foo">element</xsl:element>      
    </xsl:template>

    <xsl:attribute-set name="bar" use-attribute-sets="foo">
	<xsl:attribute name="bar">bar</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="foo" use-attribute-sets="bar">
    </xsl:attribute-set>

</xsl:stylesheet>
