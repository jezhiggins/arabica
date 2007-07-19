<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="att"></xsl:attribute>
        <xsl:attribute name="att1">1</xsl:attribute>
        <xsl:attribute name="att2">2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="empty"/>

    <xsl:template match="/">
        <!-- test that xslatt override specified att -->
	<xsl:element name="elem" use-attribute-sets="foo empty">
		<xsl:attribute name="att2">elem</xsl:attribute> 
		<xsl:attribute name="att1">elem</xsl:attribute> 
	</xsl:element>
    </xsl:template>

</xsl:stylesheet>
