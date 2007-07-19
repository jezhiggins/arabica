<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="book">
        <xsl:value-of select="title"></xsl:value-of>
        

        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
