<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:my="http://my.com">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>
	<xsl:template match="text()"></xsl:template>

	<!-- Split unioned queries by priority -->
	<xsl:template match="bookstore" priority="0.25">2<xsl:apply-templates/></xsl:template>

	<xsl:template match="/ | bookstore">1<xsl:apply-templates/></xsl:template>

	<xsl:template match="book | my:book | * | my:*">3<xsl:apply-templates/></xsl:template>

	<xsl:template match="book | my:book | * | my:*" priority="-.1">4<xsl:apply-templates/></xsl:template>

</xsl:stylesheet>
