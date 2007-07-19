<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="att"></xsl:attribute>
        <xsl:attribute name="att2">2</xsl:attribute>
        <xsl:attribute name="att2">2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
	<!-- attribute specified in the literal element will override what is in the attribute set -->
    	<foo name="foo" att="abc" elem1="value1" xsl:use-attribute-sets="foo" elem2="value2" att1="def"/>
	
    	<xsl:element name="foo" xsl:use-attribute-sets="foo" >
		<xsl:attribute name="bar">bar</xsl:attribute>
	</xsl:element>
    </xsl:template>

</xsl:stylesheet>
