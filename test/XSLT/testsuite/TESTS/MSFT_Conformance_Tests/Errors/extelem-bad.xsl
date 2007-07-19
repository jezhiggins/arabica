<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" extension-element-prefixes="foo" xmlns:foo="http://my.com">

    <xsl:output encoding="UTF-8"/>

    <xsl:template match="/">
        <xsl:comment> No fallback defined </xsl:comment>
        <foo:x/>
    </xsl:template>

</xsl:stylesheet>
