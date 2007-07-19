<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- xsl:output does not contain a method, default to XML -->
    <xsl:output doctype-public="public"/>

    <xsl:template match="/">

        <!-- Non-whitespace text nodes forces default to XML -->
        <xsl:text>some text</xsl:text>
        <html>
            <head/>
            <h1> <b>Hello</b> </h1>
        </html>
    </xsl:template>

</xsl:stylesheet>
