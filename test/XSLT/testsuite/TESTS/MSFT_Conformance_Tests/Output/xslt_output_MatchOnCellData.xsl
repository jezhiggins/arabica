<?xml version='1.0'?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="html" encoding='utf-8' indent='no' />

	<xsl:template match="/">
	   <HTML>
		<xsl:apply-templates />
	   </HTML>
	</xsl:template>

	<xsl:template match="//CellData">
		FooBar
	</xsl:template>

</xsl:stylesheet>

