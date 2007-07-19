<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="xslTutorial">
          
XML Declaration expected: method=
        <xsl:value-of select="$meth"></xsl:value-of>
        
 omit-xml-declaration=
        <xsl:value-of select="$dec"></xsl:value-of>
        
 indent=
        <xsl:value-of select="$ind"></xsl:value-of>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
    <xsl:template match="*">
        <xsl:value-of select="name()"></xsl:value-of>
        <xsl:apply-templates></xsl:apply-templates>
    </xsl:template>
</xsl:stylesheet>
