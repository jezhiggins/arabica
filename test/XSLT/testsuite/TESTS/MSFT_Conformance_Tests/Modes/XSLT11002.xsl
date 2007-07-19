<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:abc="urn:foo">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
    <xsl:apply-templates mode=":xyz"/>
</xsl:template>

<xsl:template match="book" mode=":xyz">
    <SPAN style="color=blue">
        <xsl:value-of select="name()"/> :<xsl:value-of select="title"/> 
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>

<xsl:template match="text()" mode=":xyz">
</xsl:template>

<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>
