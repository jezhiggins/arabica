<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="http://my.com" exclude-result-prefixes="foo">
    <xsl:output method="html" version="4.0" encoding="utf-8"/>

    <xsl:template match="/">
	<AREA href="&amp;{{myrect(imageuri)}};"/>
    </xsl:template>
</xsl:stylesheet>