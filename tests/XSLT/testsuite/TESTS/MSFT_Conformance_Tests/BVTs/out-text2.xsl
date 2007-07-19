<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Set encoding to UTF-8 -->
    <xsl:output method="text" encoding="UTF-8"/>

    <!-- This overrides the previous "text" method -->
    <xsl:output method="xsl:my-method"/>

    <!-- Since the original text was overriden, output encoding will default to UTF-16 -->
    <xsl:output method="text"/>

    <xsl:template match="/">
        <html>Hello</html>
    </xsl:template>

</xsl:stylesheet>
