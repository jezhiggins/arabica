<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<xsl:template match="//book">
		<xsl:variable name="{node()}"> foo </xsl:variable>
		<a href="foo"/>
	</xsl:template>
</xsl:stylesheet>
