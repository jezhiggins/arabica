<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Test case for bug 71240, duplicate parameter -->

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <xsl:apply-templates select="/">
            <xsl:with-param name="foo"/>
            <xsl:with-param name="foo"/>
        </xsl:apply-templates>

    </xsl:template>

</xsl:stylesheet>