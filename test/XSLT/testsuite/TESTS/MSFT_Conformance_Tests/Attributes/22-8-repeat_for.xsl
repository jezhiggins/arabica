<?xml version='1.0' ?>
<!DOCTYPE xsl:stylesheet [
	<!ELEMENT xsl:stylesheet ANY>		<!ATTLIST xsl:stylesheet xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" version CDATA #FIXED "1.0">
	<!ELEMENT xsl:template ANY>	<!ATTLIST xsl:template xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" match CDATA #IMPLIED>
	<!ELEMENT xsl:for-each ANY>	<!ATTLIST xsl:for-each xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ELEMENT xsl:value-of ANY>	<!ATTLIST xsl:value-of xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ATTLIST xsl:for-each
		select CDATA #IMPLIED>
	<!ATTLIST xsl:value-of
		select CDATA #IMPLIED>
	<!ENTITY test "//item" >
	<!ELEMENT xsl:output ANY>		<!ATTLIST xsl:output method CDATA #IMPLIED omit-xml-declaration CDATA #IMPLIED>
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:for-each select="&test;" >
-----------
<xsl:value-of select="common" />
-----------
	</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
