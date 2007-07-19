<!DOCTYPE xsl:stylesheet [
	<!ELEMENT xsl:stylesheet ANY>		<!ATTLIST xsl:stylesheet xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" version CDATA #FIXED "1.0">
	<!ELEMENT	xsl:apply-templates	ANY>
	<!ELEMENT	xsl:template		ANY>
	<!ELEMENT	xsl:value-of		ANY>
	<!ELEMENT	hr			ANY>
	<!ELEMENT	xsl:sort			ANY> <!ATTLIST xsl:sort select CDATA #IMPLIED>
	<!ELEMENT xsl:output ANY>		<!ATTLIST xsl:output method CDATA #IMPLIED omit-xml-declaration CDATA #IMPLIED>

	<!ATTLIST xsl:value-of	select CDATA #IMPLIED>
	<!ATTLIST xsl:apply-templates 
		select CDATA #IMPLIED
		order-by CDATA #IMPLIED>
	<!ENTITY test "common">

	<!ATTLIST xsl:template 		  xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" match CDATA #IMPLIED>
	<!ATTLIST xsl:apply-templates	  xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ATTLIST xsl:value-of		  xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
]>

<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
   <xsl:apply-templates select="//item">
	<xsl:sort select="&test;"/>
   </xsl:apply-templates>	
</xsl:template>

<xsl:template match="item">
		<hr/>
		<xsl:value-of select="common" />
		<xsl:value-of select="latin" />
		<xsl:value-of select="common" />
		<hr/>
</xsl:template>
</xsl:stylesheet>
