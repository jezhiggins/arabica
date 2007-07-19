<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <!-- Ignore attribute added at top level -->
        <xsl:attribute name="foo">bar</xsl:attribute>

        <!-- Ignore attribute, pi, element, comment, within attribute -->
        <xsl:element name="foo-elem">
            <xsl:attribute name="foo-attr"
                ><xsl:text>val</xsl:text
                ><xsl:attribute name="foo-attr"
                /><xsl:processing-instruction name="style">val</xsl:processing-instruction
                ><xsl:element name="bar"
                /><xsl:comment
            /></xsl:attribute>
        </xsl:element>

        <!-- Ignore attribute added to element after children -->
        <xsl:element name="foo-elem">
            <xsl:text>text</xsl:text>
            <xsl:attribute name="foo-attr">val</xsl:attribute>
        </xsl:element>

        <!-- Ignore pi, element, comment, within pi (attribute OK, non-spec) -->
        <xsl:processing-instruction name="style"
            ><xsl:text>val</xsl:text
            ><xsl:attribute name="pi-attr">val</xsl:attribute
            ><xsl:processing-instruction name="style2"
            /><xsl:element name="foo-elem"
            /><xsl:comment
        /></xsl:processing-instruction>

        <!-- Ignore pi, element, comment, attribute, within comment -->
        <xsl:comment
            ><xsl:text> comment </xsl:text
            ><xsl:processing-instruction name="style"
            /><xsl:element name="foo-elem"
            /><xsl:comment
            /><xsl:attribute name="foo-attr"
        /></xsl:comment>
    </xsl:template>
</xsl:stylesheet>