<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output omit-xml-declaration="yes" method="xml" indent="yes" encoding="UTF-8"/>

    <xsl:template match="/">
        <xsl:copy-of select=".//author"/>
    </xsl:template>

</xsl:stylesheet>