<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href = "91173a.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="book[@style='autobiography']">
    <SPAN style="color=blue">
    <xsl:value-of select="name()"/> : <xsl:value-of select="title"/>     
    <xsl:apply-imports/>
    </SPAN><br/>
</xsl:template>

<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>