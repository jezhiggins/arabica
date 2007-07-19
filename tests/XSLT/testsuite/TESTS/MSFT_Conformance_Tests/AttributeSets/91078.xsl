<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
    <!--
        <xsl:attribute name="attr" use-attribute-sets="notDeclared">123</xsl:attribute>
        -->
        <xsl:attribute name="attr" >123</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
    	<foo xsl:use-attribute-sets="foo"/>
    </xsl:template>

</xsl:stylesheet>
