<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="no"/>

    <xsl:preserve-space elements="*"/>

    <xsl:template match="/">
       <!-- Preceding query (selection) -->
       <preceding-count><xsl:value-of select="count(html/my:element/preceding::text())"/></preceding-count>
    </xsl:template>

</xsl:stylesheet>
