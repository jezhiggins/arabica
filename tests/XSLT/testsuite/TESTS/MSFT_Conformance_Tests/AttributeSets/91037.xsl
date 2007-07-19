<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="attr">simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="simple" use-attribute-sets="complex">
        <xsl:attribute name="attr">simple1</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="bookstore">
	<foo xsl:use-attribute-sets="simple foo" use-attribute-sets="display as specified"/>
	<foo xsl:use-attribute-sets="foo simple" use-attribute-sets="display as specified"/>
    </xsl:template>

    <xsl:attribute-set name="complex">
        <xsl:attribute name="att1">complex1</xsl:attribute>
        <xsl:attribute name="{$x}">complex2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:param name="x">param-att</xsl:param>
</xsl:stylesheet>
