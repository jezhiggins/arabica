<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 	xmlns:my="http://my.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Built-in rules should only be invoked if not explicitly specified (have lower priority than anything else) -->
	<xsl:template match="text()" priority="-99999999999999999"></xsl:template>
	<xsl:template match="text()" mode="Second"></xsl:template>

	<!-- Built-in rule should print out attribute values -->
	<xsl:template match="subscription"><xsl:apply-templates select="@*"/></xsl:template>

	<!-- Built-in rule should print out value of text nodes -->
	<xsl:template match="last-name"><xsl:apply-templates mode="TextMode"/></xsl:template>

	<!-- Modes should not be invoked by built-in rules unless an explicit rule already matched that mode -->
	<xsl:template match="author" mode="First">ERROR</xsl:template>

	<!-- At every award, restart processing in a different mode -->
	<xsl:template match="award"><xsl:apply-templates select="/" mode="Second"/></xsl:template>

	<!-- Mode should be inherited by built-in element template rule -->
	<xsl:template match="my:title" mode="Second"><xsl:value-of select="text()"/></xsl:template>

</xsl:stylesheet>
