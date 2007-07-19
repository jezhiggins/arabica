<!-- UTF-8 -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Whitespace should only be inserted after PCDATA nodes that are children of an ELEMENT -->
    <xsl:element name="foo-elem">
        <xsl:attribute name="foo-attr">
            <xsl:text>Hello</xsl:text>
        </xsl:attribute>
        <xsl:text>Hello</xsl:text>
        <xsl:processing-instruction name="style">
            <xsl:text>Hello</xsl:text>
        </xsl:processing-instruction>
        <xsl:comment>
            <xsl:text>Hello</xsl:text>
        </xsl:comment>
    </xsl:element>
</html>
