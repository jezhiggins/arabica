<?xml version='1.0' ?>
<!DOCTYPE xsl:stylesheet SYSTEM 'stylesheet.dtd' [
	<!ATTLIST xsl:for-each
		xmlns:xsl	CDATA	#FIXED	"http://www.w3.org/1999/XSL/Transform"
		>
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:for-each select="//Section"><xsl:value-of select="Title"/></xsl:for-each>
</xsl:template></xsl:stylesheet>