<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<!--Mode attribute whose value contains invalid characters-->

<xsl:template match="/">
    <xsl:apply-templates mode="1234"/>
</xsl:template>

<xsl:template match="book" mode="1234">
    <SPAN style="color=red">
        <xsl:value-of select="name()"/> :<xsl:value-of select="title"/> 
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>

</xsl:stylesheet>
