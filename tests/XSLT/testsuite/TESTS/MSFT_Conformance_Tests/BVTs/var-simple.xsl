<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Variables of simple types (no node-lists) -->

	<xsl:variable name="num" select="1"/>
	<xsl:variable name="str" select="'1000'"/>
	<xsl:variable name="bool" select="true()"/>

	<xsl:template match="/">
		<num><xsl:value-of select="number($num) + number($str) + number($bool)"/></num>

		<!-- Ensure that variables are evaluated using the context in which they were declared -->
		<xsl:for-each select=".//author">
			<xsl:variable name="foo" select="position()"/>
			<xsl:for-each select="/bookstore">
				<xsl:value-of select="$foo"/>
			</xsl:for-each>
		</xsl:for-each>

		<!-- Ensure that variable in non-query container uses query of outer container -->
		<xsl:if test="$num">
			<xsl:variable name="foo" select="position() + 50"/>
			<xsl:for-each select="/bookstore">
				<xsl:value-of select="$foo"/>
			</xsl:for-each>
			<xsl:value-of select="($foo + $foo) * $foo"/>
		</xsl:if>

        <!-- Use variables in xsl:sort and xsl:with-param elements -->
        <xsl:for-each select="//book">
            <xsl:variable name="author" select="author"/>
            <xsl:apply-templates select="$author">
                <xsl:sort select="$author"/>
                <xsl:with-param name="last-name" select="$author/last-name"/>
            </xsl:apply-templates>
        </xsl:for-each>
	</xsl:template>

    <xsl:template match="author">
        <xsl:param name="last-name"/>
        <names><xsl:copy-of select="$last-name"/></names>
    </xsl:template>

</xsl:stylesheet>
