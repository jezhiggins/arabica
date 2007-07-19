<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Explicit priorities -->
	<xsl:template match="/">root&#10;<xsl:apply-templates select="bookstore/book"/></xsl:template>

	<xsl:template match="book" priority="10.0000000000001">book  pri 10.000...  1st&#10;</xsl:template>

	<xsl:template match="book" priority="10.0000000000001">book  pri 10.000...  2nd&#10;</xsl:template>

	<xsl:template match="book" priority="10">book  pri 10&#10;</xsl:template>

	<xsl:template match="book" priority="9.99999999999999">book  pri 9.999...&#10;</xsl:template>

	<xsl:template match="book" priority="-10">book pri -10&#10;</xsl:template>

</xsl:stylesheet>
