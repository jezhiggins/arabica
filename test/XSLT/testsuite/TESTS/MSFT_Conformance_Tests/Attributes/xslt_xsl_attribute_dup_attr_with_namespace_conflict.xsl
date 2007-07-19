<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output encoding="UTF-8" indent="no" omit-xml-declaration="yes"/>

<xsl:template match="/">
    <p xmlns:foo="urn:foo">
        <p foo:attr="val">
            <xsl:attribute name="foo:attr" xmlns:foo="urn:foo2"/>
        </p>
    </p>
</xsl:template>

</xsl:stylesheet>