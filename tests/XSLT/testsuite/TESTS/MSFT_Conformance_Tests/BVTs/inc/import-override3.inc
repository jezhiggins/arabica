<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="last-name">
        <override3-last-name/><xsl:text>&#10;</xsl:text>

        <!-- This apply-imports does not match, so built-in template should take over -->
        <xsl:apply-imports/><xsl:text>&#10;</xsl:text>
    </xsl:template>

</xsl:stylesheet>
