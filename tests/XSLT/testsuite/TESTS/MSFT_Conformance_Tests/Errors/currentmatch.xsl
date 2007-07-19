<!-- Error Case -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:my="http://my.com">
    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:template match="foo[current()]">
    </xsl:template>
</xsl:stylesheet>
