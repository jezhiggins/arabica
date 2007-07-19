<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/" priority="8">
A
</xsl:template>

<xsl:template match="/" priority="1,0">
B
</xsl:template>

<xsl:template match="/" priority="5">
C
</xsl:template>

</xsl:stylesheet>