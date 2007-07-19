<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="urn:http//www.placeholder-name-here.com/schema/" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="my:book[@style='leather']">
    <SPAN style="color=orange">
    From D <xsl:value-of select="name()"/> : <xsl:value-of select="my:title"/> 
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>


<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>