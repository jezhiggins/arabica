<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">
        <format><xsl:value-of select="format-number(.12, '.000')"/></format>
    </xsl:template>

</xsl:stylesheet>