<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Purpose: Test case for bug 70935 -->

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">
        <test><xsl:copy-of select="document('')/xsl:stylesheet/namespace::xsl"/></test>
    </xsl:template>

</xsl:stylesheet>