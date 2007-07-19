<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- xsl:output does not contain a method, default to XML -->
    <xsl:output doctype-system="system"/>

    <xsl:template match="/">

        <xsl:text xml:space="preserve">             </xsl:text>

        <!-- Non HTML document element forces default to XML -->
        <html xmlns="http://my.com">
            <head/>
            <h1> <b>Hello</b> </h1>
        </html>
    </xsl:template>

</xsl:stylesheet>
