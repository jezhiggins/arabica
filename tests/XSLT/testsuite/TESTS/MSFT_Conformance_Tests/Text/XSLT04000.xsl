<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:text invalid-attribute="yes">This has an invalid-attribute="yes" which XSLT ignores</xsl:text>
    </xsl:template>
</xsl:stylesheet>
