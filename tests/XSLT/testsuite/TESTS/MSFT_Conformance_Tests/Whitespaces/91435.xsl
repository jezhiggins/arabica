<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="yes"/>

    <xsl:strip-space elements="*"/>

    <xsl:template match="/">
        <!-- Self query (matching) -->
        <self-count><xsl:value-of select="count(//self::node()[parent::html])"/></self-count>
    </xsl:template>

</xsl:stylesheet>
