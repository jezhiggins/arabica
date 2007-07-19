<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:import href="import-override2.inc"/>
    <xsl:import href="import-override2.inc"/>
    <xsl:import href="import-override2.inc"/>
    <xsl:import href="import-override2.inc"/>

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
	<!-- Call apply-imports from within an imported file -->
        <override-slash/>
	<xsl:apply-imports/>
    </xsl:template>

    <xsl:template match="bookstore">
        <override-bookstore/>
	<xsl:for-each select=".">
		<!-- for-each should not disallow apply-imports in invoked apply-templates -->
	        <xsl:apply-templates select="book" mode="book-mode"/>
	</xsl:for-each>
    </xsl:template>

    <xsl:template match="book" mode="book-mode">
        <override-book/>
        <xsl:apply-templates select="author/last-name"/>
    </xsl:template>

</xsl:stylesheet>
