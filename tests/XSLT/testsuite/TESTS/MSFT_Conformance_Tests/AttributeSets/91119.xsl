<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo" >
	<xsl:attribute name="foo" >
        <xsl:copy />     <!-- this xsl:copy is causing the inpartial output -->
		<xsl:element name="abc"/>
		<xsl:value-of select="'testing'"/>
	</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="bookstore">
	<xsl:element name="elem" use-attribute-sets="foo">element</xsl:element>      
    </xsl:template>

</xsl:stylesheet>
