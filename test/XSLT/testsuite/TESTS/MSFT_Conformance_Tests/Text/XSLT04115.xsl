<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/" xmlns:NS5="http://www.w3.org/XML/1998/namespace" NS5:space="default" NS5:lang="en">
        <xsl:for-each select="test">
            <xsl:apply-templates select="case"></xsl:apply-templates>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="case">
        <xsl:value-of select="."></xsl:value-of>
    </xsl:template>
</xsl:stylesheet>
