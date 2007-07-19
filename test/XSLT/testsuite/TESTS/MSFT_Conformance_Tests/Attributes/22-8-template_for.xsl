<?xml version="1.0" ?>

<!DOCTYPE xsl:stylesheet [
	<!ELEMENT xsl:stylesheet ANY>		<!ATTLIST xsl:stylesheet xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" version CDATA #FIXED "1.0">
	<!ELEMENT xsl:template ANY>		<!ATTLIST xsl:template xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ELEMENT xsl:apply-templates ANY>	<!ATTLIST xsl:apply-templates xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ELEMENT xsl:comment ANY>		<!ATTLIST xsl:comment xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ELEMENT xsl:output ANY>		<!ATTLIST xsl:output method CDATA #IMPLIED omit-xml-declaration CDATA #IMPLIED>

	<!ATTLIST xsl:apply-templates
		select CDATA #IMPLIED>

	<!ATTLIST xsl:template
		match CDATA #IMPLIED>

	<!ENTITY test "Plant-Sheet" >
]>


<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
<xsl:apply-templates select="*" />
</xsl:template>

<xsl:template match="&test;">
Some text in the template
<xsl:comment>This is the end of the template section of the stylesheet</xsl:comment>
</xsl:template>



</xsl:stylesheet>
