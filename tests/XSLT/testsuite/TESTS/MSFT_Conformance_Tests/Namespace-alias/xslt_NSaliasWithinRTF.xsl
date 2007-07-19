<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:axsl="http://my.com"
    exclude-result-prefixes="axsl">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>

    <!-- Use aliases within a result-tree-fragment -->
    <xsl:variable name="rtf">
        <axsl:template match="/" axsl:version="2.0"/>
    </xsl:variable>

    <xsl:template match="/">
        <xsl:copy-of select="$rtf"/>
    </xsl:template>

</xsl:stylesheet>