<?xml version="1.0" ?>
<!DOCTYPE xsl:stylesheet SYSTEM "stylesheet.dtd" [
	<!ATTLIST xsl:for-each	select CDATA #IMPLIED>
	<!ATTLIST xsl:element	select CDATA #IMPLIED>
]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:for-each select="/Plant-Sheet/Section" >
		<xsl:apply-templates select="Title" />
	</xsl:for-each>
</xsl:template>	

<xsl:template match="*">
	<xsl:value-of select="."/>:
</xsl:template>

</xsl:stylesheet>