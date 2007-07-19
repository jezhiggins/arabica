<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<xsl:apply-templates select="//ListItem">
			<xsl:with-param name="Title" select="'foo'"></xsl:with-param>
		</xsl:apply-templates>
	</xsl:template>
	<xsl:template match="ListItem">
		<xsl:param name="Title" />
				1. before, <xsl:value-of select="$Title" />
				2. <xsl:call-template name="AnotherTemplate" />
				3. after, <xsl:value-of select="$Title" />
	</xsl:template>
	<xsl:template name="AnotherTemplate">bar</xsl:template>
</xsl:stylesheet>
