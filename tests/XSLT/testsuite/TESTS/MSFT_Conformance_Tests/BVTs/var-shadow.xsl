<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- Shadowing tests -->

	<xsl:variable name="foo" select="'foo 1'"/>
	<xsl:variable name="bar" select="'bar 1'"/>

	<xsl:template match="/">

		<xsl:for-each select=".//first-name">
			<xsl:variable name="bar" select="'bar 2'"/>

			<xsl:if test="1">
				<xsl:variable name="foo" select="'foo 4'"/>
				<xsl:value-of select="$foo"/><xsl:value-of select="$bar"/>
			</xsl:if>

			<xsl:variable name="foo" select="'foo 3'"/>
			<xsl:value-of select="$foo"/>
		</xsl:for-each>

		<xsl:variable name="foo" select="'foo 2'"/>

		<xsl:value-of select="$foo"/>
		<xsl:value-of select="$bar"/>

        <!-- Variables should not be visible to their content -->
        <xsl:variable name="bar">
            <xsl:variable name="bar">
                <xsl:variable name="bar">
                    <xsl:variable name="bar">
                        <xsl:value-of select="$bar"/>
                    </xsl:variable>
                </xsl:variable>
            </xsl:variable>
        </xsl:variable>
	</xsl:template>

</xsl:stylesheet>
