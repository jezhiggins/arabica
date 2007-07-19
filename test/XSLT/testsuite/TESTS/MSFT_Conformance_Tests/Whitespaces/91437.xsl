<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:preserve-space elements="*"/>

    <xsl:template match="/">
        <!-- Following query (matching and selection) -->
        <following-count><xsl:value-of select="count(html/following::text())"/></following-count>
        <following-count><xsl:value-of select="count(//following::text()[parent::html])"/></following-count>
    </xsl:template>

</xsl:stylesheet>
