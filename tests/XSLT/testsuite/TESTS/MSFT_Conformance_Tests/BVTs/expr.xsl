<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">

		<!-- Sort by a string constant, then a boolean condition -->
		<xsl:for-each select="//author">
			<xsl:sort select="'constant'"/>
			<xsl:sort select="last-name = 'Bob'"/>
			<name><xsl:value-of select="last-name"/><xsl:text>, </xsl:text><xsl:value-of select="first-name"/></name>
		</xsl:for-each>

		<!-- Use operands with if statement -->
		<xsl:if test="'non-empty'">
			<xsl:value-of select="'If test succeeded'"/>
			<xsl:if test="0">
				<xsl:value-of select="'Error'"/>
			</xsl:if>
		</xsl:if>

	</xsl:template>
</xsl:stylesheet>
