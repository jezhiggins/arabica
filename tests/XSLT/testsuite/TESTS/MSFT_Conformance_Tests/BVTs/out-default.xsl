<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- xsl:output does not contain a method, default to HTML -->
    <xsl:output doctype-system="system"/>

    <xsl:template match="/">

        <!-- Whitespace nodes should not keep HTML from being the default output method -->
        <xsl:text xml:space="preserve">              

        </xsl:text>
        <html>
            <head/>
            <h1> <b>Hello</b> </h1>
        </html>
    </xsl:template>

</xsl:stylesheet>
