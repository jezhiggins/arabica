<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
	<!-- abc should override 123 -->
        <xsl:attribute name="attr">123</xsl:attribute>
        <xsl:attribute name="attr" >abc</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
    	<foo xsl:use-attribute-sets="foo"/>
	<xsl:element name="elem" use-attribute-sets="simple"/>
    </xsl:template>

    <xsl:attribute-set name="simple" use-attribute-sets="complex">
    </xsl:attribute-set>

    <xsl:attribute-set name="complex" use-attribute-sets="foo">
    </xsl:attribute-set>

</xsl:stylesheet>
