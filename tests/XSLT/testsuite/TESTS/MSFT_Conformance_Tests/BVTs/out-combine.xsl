<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="http://my.com">

    <!-- xsl:output elements combine with each other -->
    <xsl:output media-type="a little of this, a little of that"/>

    <xsl:output method="xml" encoding="UTF-8"/>

    <xsl:output method="foo:bar" doctype-public="PUBLIC"/>

    <xsl:output method="html" indent="no"/>

    <xsl:template match="/">

        <html>
            <head/>
            <h1> <b>Hello</b> </h1>
        </html>
    </xsl:template>

</xsl:stylesheet>
