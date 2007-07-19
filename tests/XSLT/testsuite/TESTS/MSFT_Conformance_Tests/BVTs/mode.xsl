<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com" xmlns:my2="http://my.com" xmlns="http://my.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">root&#10;<xsl:apply-templates mode="First"/></xsl:template>

	<xsl:template match="bookstore" mode="First">First&#10;<xsl:apply-templates select="." mode="my:Second"/></xsl:template>

	<!-- Switch back to null mode -->
	<xsl:template match="bookstore" mode="my2:Second" priority="2">my:Second  pri 2&#10;<xsl:apply-templates select="."/></xsl:template>

	<!-- Make sure that templates in other modes are correctly sorted by priority -->
	<xsl:template match="bookstore" mode="my2:Second" priority="1">my:Second  pri 1&#10;</xsl:template>

	<!-- Default namespace shouldn't be used in resolving modes -->
	<xsl:template match="bookstore" mode="Second">ERROR&#10;</xsl:template>

	<xsl:template match="bookstore" mode="Error">ERROR&#10;</xsl:template>

	<xsl:template match="bookstore">empty mode&#10;<xsl:apply-templates mode="NotInDoc" select="NoSuchElement"/></xsl:template>

</xsl:stylesheet>
