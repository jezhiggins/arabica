<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	howdy
	<xsl:apply-templates select="//item" />
</xsl:template>	

<xsl:template match="item">
	XXX
</xsl:template>

</xsl:stylesheet>