<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:preserve-space elements="*"/>

    <xsl:template match="/">
        <!-- Following-sibling query (selection) -->
        <following-sibling-count><xsl:value-of select="count(html/h1/following-sibling::text())"/></following-sibling-count>
    </xsl:template>

</xsl:stylesheet>
