<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:strip-space elements="*"/>

    <xsl:template match="/">
        <!-- Children query (matching and selection) -->
        <child-count><xsl:value-of select="count(html/child::node())"/></child-count>
        <child-count><xsl:value-of select="count(//child::node()[parent::html])"/></child-count>
    </xsl:template>

</xsl:stylesheet>
