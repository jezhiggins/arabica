<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/ | author">
        <xsl:param name="foo"><author>Andy Kimball</author></xsl:param>

        <xsl:copy-of select="$foo"/>
        <xsl:value-of select="'&#10;&#10;'"/>

        <xsl:variable name="bar">
            <xsl:for-each select=".//author">
                <xsl:apply-templates select=".">
                    <xsl:with-param name="foo"><xsl:copy-of select="."/></xsl:with-param>
                </xsl:apply-templates>
            </xsl:for-each>
        </xsl:variable>

        <xsl:copy-of select="$bar"/>

    </xsl:template>

</xsl:stylesheet>
