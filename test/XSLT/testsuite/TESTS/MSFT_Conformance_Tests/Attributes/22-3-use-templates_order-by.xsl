<?xml version='1.0' ?>
<!DOCTYPE xsl:stylesheet SYSTEM 'stylesheet.dtd' [
	<!ATTLIST xsl:apply-templates
		xmlns:xsl	CDATA	#FIXED	"http://www.w3.org/1999/XSL/Transform"
		>
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:apply-templates select="//Section/Title"/>
</xsl:template>

<xsl:template match="*">
	<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>