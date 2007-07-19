<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:variable name="xsl:bookstore" select="bookstore"/>

	<xsl:template match="/">
        <xsl:for-each select="$xsl:bookstore/book">
		    <xsl:apply-templates select=".">
			    <xsl:with-param name="xsl:foo" select="author"/>
		    </xsl:apply-templates>
        </xsl:for-each>
	</xsl:template>

	<xsl:template match="book">
		<xsl:param name="xsl:foo"/>
		<xsl:param name="deep" select="0"/>

		<xsl:element name="level{$deep}">
		<!-- Nested loops, both referencing same variable -->
		<xsl:for-each select="$xsl:foo/last-name">
			<xsl:for-each select="$xsl:foo/last-name">
				<xsl:value-of select="$xsl:foo/first-name"/>
			</xsl:for-each>
		</xsl:for-each>
		</xsl:element>

		<!-- Recursive call -->
		<xsl:if test="$deep &lt; 2">
			<xsl:apply-templates select=".">
				<xsl:with-param name="xsl:foo" select="$xsl:foo"/>
				<xsl:with-param name="deep" select="$deep + 1"/>
			</xsl:apply-templates>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
