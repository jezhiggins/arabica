<!DOCTYPE xsl:stylesheet SYSTEM 'stylesheet.dtd' [
	<!ATTLIST xsl:template
		match CDATA #IMPLIED>
]>

<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="Author">
	<xsl:apply-templates select="//*"/>
</xsl:template>

<xsl:template match="*">
	<xsl:value-of select="name()"/>
</xsl:template>

</xsl:stylesheet>
