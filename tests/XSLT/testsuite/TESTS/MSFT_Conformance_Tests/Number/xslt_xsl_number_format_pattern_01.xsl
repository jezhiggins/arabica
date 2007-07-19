<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com" exclude-result-prefixes="my">
    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
        <x><xsl:number value="12" format="01"/></x>
    </xsl:template>
</xsl:stylesheet>