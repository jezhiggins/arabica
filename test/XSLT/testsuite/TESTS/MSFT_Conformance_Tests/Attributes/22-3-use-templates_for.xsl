<?xml version='1.0' ?>
<!DOCTYPE xsl:stylesheet SYSTEM 'stylesheet.dtd' [
	<!ATTLIST xsl:apply-templates
		xmlns:xsl	CDATA	#FIXED	"http://www.w3.org/1999/XSL/Transform"
		select		CDATA	"//Section/*" >
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="Title">
	<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>