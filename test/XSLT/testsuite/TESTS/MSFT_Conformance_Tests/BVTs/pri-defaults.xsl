<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com" xmlns="http://myother.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Default priorities -->
	<xsl:template match="/"
		><xsl:text>root&#10;</xsl:text
		><xsl:apply-templates select="bookstore/my:book"
		/><xsl:apply-templates select="bookstore/@*"
		/><xsl:apply-templates select="processing-instruction()"
	/></xsl:template>

	<xsl:template match="/bookstore/my:book">/bookstore/my:book  pri 0.5&#10;<xsl:apply-templates select="node()"/><xsl:apply-templates select="@*"/></xsl:template>

	<xsl:template match="my:title">my:title  pri 0&#10;</xsl:template>

	<xsl:template match="my:book">my:book  pri 0&#10;</xsl:template>

	<xsl:template match="my:*">my:*  pri -0.25&#10;</xsl:template>

	<!-- Need processing-instruction(Literal) test when that functionality becomes available -->

	<xsl:template match="processing-instruction">ERROR&#10;</xsl:template>

	<xsl:template match="node()">node()  pri -0.5&#10;</xsl:template>

	<xsl:template match="@xmlns:*">@xmlns:*  pri -0.25&#10;</xsl:template>

	<xsl:template match="@*">@*  pri -0.5&#10;</xsl:template>

</xsl:stylesheet>
