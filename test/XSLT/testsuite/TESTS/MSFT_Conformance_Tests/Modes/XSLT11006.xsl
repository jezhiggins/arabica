<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
    <xsl:apply-templates mode="x"/>
</xsl:template>

<xsl:template match="book" priority="1" mode="x">
    <SPAN style="color=red">
        <xsl:value-of select="name()"/> :<xsl:value-of select="title"/> 
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>

<xsl:template match="book" priority="1" mode="x">
    <SPAN style="color=blue">
        <xsl:value-of select="name()"/> :<xsl:value-of select="title"/>
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>

<xsl:template match="text()" mode="x">
</xsl:template>

<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>
