<?xml version='1.0'?>
<!DOCTYPE xsl:stylesheet SYSTEM "stylesheet1.dtd" [
	<!ATTLIST xsl:stylesheet
		xmlns:xsl		CDATA	#FIXED	"http://www.w3.org/1999/XSL/Transform" 
		version			CDATA	"1.0" >
]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="/">
<xsl:for-each select="/bookstore/magazine/title">
     <xsl:value-of select="."/> 
</xsl:for-each>

<xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>