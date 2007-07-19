<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="/">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="message">
<xsl:message terminate="yes" foo="bar">
    <xsl:value-of select="text()"/>
</xsl:message>
</xsl:template>    

<xsl:template match="text()"/>

</xsl:stylesheet>