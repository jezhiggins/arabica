<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
		<xsl:apply-templates/>
	</xsl:template>

	<!-- Regress bug 66082: /node() crashes -->
	<xsl:template match="/node()[name() = 'bookstore']">
		<xsl:apply-templates select="*" xml:space="preserve">
			<!-- Comment -->
			<xsl:sort select="@style" order="ascending" data-type="text"/>
			<xsl:sort select="title/text()" order="descending"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="bookstore/*">
		<title-text><xsl:value-of select="@style"/>, <xsl:value-of select="title/text() | my:title/text()" /></title-text>
	</xsl:template>
</xsl:stylesheet>
