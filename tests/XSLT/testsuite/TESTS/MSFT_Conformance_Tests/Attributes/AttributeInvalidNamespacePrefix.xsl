<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <root>
            <xsl:attribute name="{'xmlns:foo'}" namespace="my-namespace">http://default-namespace</xsl:attribute>
            <xsl:attribute name="{'xmlns:foo'}"                         >http://default-namespace</xsl:attribute>
        </root>
    </xsl:template>
</xsl:stylesheet>
