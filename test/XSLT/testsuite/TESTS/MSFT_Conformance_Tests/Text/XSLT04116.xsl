<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/" xml:space="preservedefault">
        <xsl:for-each select="test">
            <xsl:apply-templates></xsl:apply-templates>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="test">
        <xsl:value-of select="case"></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
