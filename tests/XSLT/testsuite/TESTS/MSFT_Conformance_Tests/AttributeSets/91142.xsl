<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="no" indent="yes"/>

    <xsl:attribute-set name="foo" use-attribute-sets="bar" >
        <xsl:attribute name="attr">123</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
    	<foo xsl:use-attribute-sets="foo bar"/>
    </xsl:template>

    <xsl:attribute-set name="bar" use-attribute-sets="blue">
        <xsl:attribute name="attrbar">abc</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="blue" use-attribute-sets="gee">
        <xsl:attribute name="attrbar">abc</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="gee" use-attribute-sets="foo">
        <xsl:attribute name="attrbar">abc</xsl:attribute>
    </xsl:attribute-set>

</xsl:stylesheet>
