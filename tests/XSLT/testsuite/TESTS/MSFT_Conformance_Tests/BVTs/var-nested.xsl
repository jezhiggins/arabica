<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/ | bookstore">

		<xsl:param name="abs" select="/"/>
		<xsl:param name="bookstore" select="$abs/bookstore[1]"/>
		<xsl:param name="magazine" select="$bookstore//magazine"/>
		<xsl:param name="articles" select="$magazine/./articles"/>
		<xsl:param name="story1" select="$articles/story1"/>

		<xsl:variable name="relative" select="bookstore"/>

		<p>
		<xsl:for-each select="$story1">
			<xsl:for-each select="$story1">
				<xsl:sort select="."/>
				<xsl:value-of select="."/>
				<xsl:apply-templates select="$relative">
					<xsl:with-param name="abs" select="/"/>
					<xsl:with-param name="bookstore" select="$bookstore"/>
					<xsl:with-param name="magazine" select="$magazine"/>
					<xsl:with-param name="story1" select="$articles/story2"/>
				</xsl:apply-templates>
			</xsl:for-each>
		</xsl:for-each>
		</p>
	</xsl:template>

</xsl:stylesheet>
