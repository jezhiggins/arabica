<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:import href="91091a.xsl"/>
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo"/>

    <xsl:template match="/">
	<xsl:element name="elem" use-attribute-sets="foo empty">
		<xsl:attribute name="att">elem</xsl:attribute> 
	</xsl:element>
    </xsl:template>
</xsl:stylesheet>

