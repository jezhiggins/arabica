<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- Simple parameter types -->

	<xsl:template match="*"/>

	<xsl:template match="/">
		<xsl:apply-templates>
            <!-- Comments and PI's allowed here -->
            <?my-pi?>
			<xsl:with-param name="string" select="'duplicate'"/>
			<xsl:with-param name="number" select="5"/>
			<xsl:with-param name="boolean" select="true()"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="bookstore">
		<xsl:param name="boolean"/>
		<xsl:param name="number"/>
		<xsl:param name="string"/>

		<x><xsl:value-of select="$string"/></x>
		<x><xsl:value-of select="$number"/></x>
		<x><xsl:value-of select="$boolean"/></x>

		<!-- Call with no matching parameters -->
		<xsl:apply-templates select="book">
			<xsl:with-param name="not-there" select="foo"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="book">
		<!-- Use default values -->
		<xsl:param name="bar" select="number(.//price) + 1"/>

		<x><xsl:value-of select="$bar"/></x>

		<xsl:apply-templates/>
	</xsl:template>

</xsl:stylesheet>
