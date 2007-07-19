<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/ | bookstore">

		<begin-level/>

		<xsl:variable name="x" select="."/>

		<!-- Use every XQL query object in for-each with recursion to test cloning -->
		<xsl:for-each select="/bookstore/book//author[1]/last-name | /bookstore/book//author[2]/last-name">
			<p1><xsl:value-of select="."/></p1>

			<xsl:for-each select="(ancestor-or-self::author/first-name)">
				<p2><xsl:value-of select="."/></p2>

				<xsl:apply-templates select="$x/bookstore"/>

			</xsl:for-each>
		</xsl:for-each>

		<end-level/>

	</xsl:template>

</xsl:stylesheet>
