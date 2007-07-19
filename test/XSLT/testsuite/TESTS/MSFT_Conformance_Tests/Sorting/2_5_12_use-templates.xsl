<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="/ROOT/node()">
		<xsl:sort select="." order="ascending" />
	</xsl:apply-templates>
</xsl:template>	

<xsl:template match="node()">
	<xsl:value-of select="." />#
</xsl:template>

</xsl:stylesheet>