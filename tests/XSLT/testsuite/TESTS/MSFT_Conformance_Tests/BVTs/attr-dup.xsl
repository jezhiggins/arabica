<!-- UTF-8 -->
<!-- Test duplicate attribute detection -->
<html xmlns="urn:xhtml" xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="urn:another">

    <!-- xsl:attribute overrides xsl:attribute -->
    <p>
        <xsl:attribute name="attr">val1</xsl:attribute>
        <xsl:attribute name="attr">value2</xsl:attribute>
        <xsl:attribute name="foo:attr">val3</xsl:attribute>
        <xsl:attribute name="foo:attr">value4</xsl:attribute>
    </p>

    <!-- xsl:attribute overrides literal attribute -->
    <p attr="val1" foo:attr="val3">
        <xsl:attribute name="attr"/>
        <xsl:attribute name="foo:attr">value4</xsl:attribute>
    </p>

    <!-- More than 16 attributes with total value length > 4096 (counting dup length as well) -->
    <p>
        <xsl:for-each select="(.//last-name)">
            <xsl:for-each select="(//last-name | //first-name)">
                <xsl:attribute name="attr{position()}">value of attribute <xsl:value-of select="position()"/><xsl:text> = </xsl:text><xsl:value-of select="."/></xsl:attribute>
            </xsl:for-each>
        </xsl:for-each>
    </p>

</html>
