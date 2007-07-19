<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="xslTutorial">
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:value-of select="name()"></xsl:value-of>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:variable name="meth" select="xml"></xsl:variable>
    <xsl:variable name="dec" select="yes"></xsl:variable>
    <xsl:variable name="ind" select="yes"></xsl:variable>
</xsl:stylesheet>
