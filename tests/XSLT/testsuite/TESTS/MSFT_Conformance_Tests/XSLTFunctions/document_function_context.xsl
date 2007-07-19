<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:variable name="configuration" select="document('xsltcfg.xml')"/>

<xsl:template match="/">
     <xsl:apply-templates select="document('testcat.xml')/test" />
</xsl:template>

<xsl:template match="test">

        <xsl:variable name="category" select="@category"/>

	<xsl:for-each select="$configuration">
		category : <xsl:value-of select="$category"/>
		id($category) : <xsl:value-of select="id($category)"/>
		name(id($category)) : <xsl:value-of select="name(id($category))"/>
	</xsl:for-each>

</xsl:template>

</xsl:stylesheet>