<!DOCTYPE xsl:stylesheet [
	<!ELEMENT xsl:stylesheet ANY>	<!ATTLIST xsl:stylesheet xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" version CDATA #FIXED "1.0">
	<!ELEMENT xsl:template ANY>	<!ATTLIST xsl:template xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" match CDATA #IMPLIED>
	<!ELEMENT xsl:value-of ANY>	<!ATTLIST xsl:value-of xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ATTLIST xsl:value-of select CDATA #IMPLIED>
	<!ENTITY test "//photo" >
	<!ELEMENT xsl:output ANY>		<!ATTLIST xsl:output method CDATA #IMPLIED omit-xml-declaration CDATA #IMPLIED>
]>

<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
<xsl:value-of select="&test;" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"/>
</xsl:template>
</xsl:stylesheet>
