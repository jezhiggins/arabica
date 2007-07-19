<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/" xml:space="preserve"><test><xsl:for-each select="test">&#xD;&#xA;<xsl:apply-templates select="case"></xsl:apply-templates></xsl:for-each>&#x9;&#x20;</test></xsl:template>
    <xsl:template match="case"><ws>&#xD;&#xA;<case><xsl:value-of select="."></xsl:value-of></case>&#x9;&#x20;</ws></xsl:template>
</xsl:stylesheet>
