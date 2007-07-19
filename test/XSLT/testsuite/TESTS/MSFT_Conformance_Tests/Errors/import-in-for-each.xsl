<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
        <xsl:for-each select=".">
            <xsl:if test="true()">
                <xsl:apply-imports/>
            </xsl:if>
        </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>
