<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:variable name="varName" select="'Main'" />

    <xsl:template match="/">
    <root>
        <xsl:copy-of select="$varName" />
        <xsl:call-template name="test"/>
     </root>
    </xsl:template>
   
    <xsl:template name="test">
        <xsl:variable name="varName">Sub</xsl:variable>
        <xsl:copy-of select="$varName" />
    </xsl:template>

</xsl:stylesheet>