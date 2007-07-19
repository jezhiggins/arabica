<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:variable name="foo"><ElementType name="test"><AttributeType name="attrtest"/></ElementType></xsl:variable>

    <xsl:template match="/">

        <xsl:element name="{$foo/ElementType/@name}">
            <xsl:attribute name="{$foo/ElementType/AttributeType/@name}"/>
        </xsl:element>

    </xsl:template>
</xsl:stylesheet>