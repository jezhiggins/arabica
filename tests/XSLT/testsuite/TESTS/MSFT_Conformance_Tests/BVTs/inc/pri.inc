<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

	<xsl:template match="/bookstore" priority="1">ERROR 1</xsl:template>

	<xsl:template match="nomatch/bookstore" priority="5">ERROR 2</xsl:template>

	<xsl:template match="nomatch/*" priority="4">ERROR 3</xsl:template>

	<xsl:template match="my:bookstore" priority="3">ERROR 4</xsl:template>

	<xsl:template match="my:*" priority="2">ERROR 5</xsl:template>

	<xsl:template match="bookstore" priority="1">bookstore 2</xsl:template>

</xsl:stylesheet>
