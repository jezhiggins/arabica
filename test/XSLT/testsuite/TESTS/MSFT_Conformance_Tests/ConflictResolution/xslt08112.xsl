<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<xsl:template match="text()"></xsl:template>
	<xsl:template match="x|z">
		<xsl:copy><xsl:apply-templates select="@*|node()" mode="children"/></xsl:copy>
	</xsl:template>
	<xsl:template match="x/@*" mode="children"><xsl:copy><xsl:value-of select="."/></xsl:copy></xsl:template>
	<xsl:template match="z/@*" mode="children"><xsl:copy><xsl:value-of select="."/></xsl:copy></xsl:template>
	<xsl:template match="/" mode="children"><xsl:copy/></xsl:template>
</xsl:stylesheet>
