<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="simple">
        <xsl:attribute name="attr">simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
        <xsl:element namespace="urn:foo" name="foo:elem" use-attribute-sets="simple" xsl:use-attribute-set="should be ignored" />
	<xsl:element name="complex" use-attribute-sets="complex"/>
    </xsl:template>

    <xsl:attribute-set name="complex">
        <xsl:attribute name="att1">complex1</xsl:attribute>
        <xsl:attribute name="att2">complex2</xsl:attribute>
    </xsl:attribute-set>
</xsl:stylesheet>
