<!DOCTYPE xsl:stylesheet [
	<!ELEMENT xsl:stylesheet ANY>		<!ATTLIST xsl:stylesheet xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" version CDATA #FIXED "1.0">
	<!ELEMENT xsl:template ANY>	<!ATTLIST xsl:template xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform" match CDATA #IMPLIED>
	<!ELEMENT xsl:processing-instruction ANY>		<!ATTLIST xsl:processing-instruction xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ATTLIST xsl:processing-instruction
		name CDATA #IMPLIED>
	<!ENTITY test "testcase">
	<!ELEMENT xsl:output ANY>		<!ATTLIST xsl:output method CDATA #IMPLIED omit-xml-declaration CDATA #IMPLIED>
]>

<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
BEFORE
   <xsl:processing-instruction name="&test;">
This is the content of a PI
   </xsl:processing-instruction>
AFTER
</xsl:template>
</xsl:stylesheet>
