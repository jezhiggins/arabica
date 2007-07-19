<!-- This is a test case for bug 70947  -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="bookstore">
        <xsl:apply-imports/>
    </xsl:template>
</xsl:stylesheet>