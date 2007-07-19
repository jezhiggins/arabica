<!-- This is a test case for bug 70947 -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:import href="xslt_nested_import_with_no_template_match.inc"/>

    <xsl:output encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
    <out>
        <xsl:apply-imports/>
    </out>
    </xsl:template>
</xsl:stylesheet>