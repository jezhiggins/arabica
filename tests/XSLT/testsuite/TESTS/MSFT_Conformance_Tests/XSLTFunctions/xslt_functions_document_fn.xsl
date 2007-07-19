<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Test for document function. Bug 71221 -->

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="no"/>

    <xsl:template match="/">
        <xsl:variable name="test" select=". | document('')"/>
        <test><xsl:value-of select="count($test)"/></test>
    </xsl:template>

</xsl:stylesheet>