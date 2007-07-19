<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:variable name="query" select=".//award"/>

	<xsl:template match="book"/>

	<xsl:template match="bookstore | book">
		<q1>
		<xsl:variable name="namefunc" select="name()"/>

		<xsl:for-each select="$query">
			<award><xsl:value-of select="."/></award>
			<xsl:if test="$namefunc='bookstore'">
				<xsl:apply-templates select="/bookstore/book[1]"/>
			</xsl:if>
		</xsl:for-each>

		<xsl:value-of select="$namefunc"/>
		</q1>
	</xsl:template>

</xsl:stylesheet>
