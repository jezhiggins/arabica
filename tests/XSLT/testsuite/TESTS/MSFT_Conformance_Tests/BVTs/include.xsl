<?xml version="1.0"?>
<!DOCTYPE xsl:stylesheet [
<!ELEMENT xsl:stylesheet (#PCDATA | xsl:include | xsl:output | xsl:template | contain-include)*>
<!ATTLIST xsl:stylesheet
            version CDATA #FIXED "1.0"
            xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">

<!ELEMENT contain-include (xsl:include)>

<!ELEMENT xsl:output EMPTY>
<!ATTLIST xsl:output
			method CDATA #IMPLIED
			encoding CDATA #IMPLIED
			omit-xml-declaration CDATA #IMPLIED
			indent CDATA #IMPLIED
			xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">

<!ELEMENT xsl:include EMPTY>
<!ATTLIST xsl:include
			href CDATA #IMPLIED
			xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">

<!ELEMENT xsl:template (#PCDATA)>
<!ATTLIST xsl:template
			match CDATA #IMPLIED
			xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">

<!ENTITY include SYSTEM "./inc/include.ent">
]>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<!-- This template rule should be overriden -->
	<xsl:template match="/">
		Overriden
	</xsl:template>

<!--	<xsl:template match="text()"></xsl:template>

	<!- - xsl:include from external entity - ->
	&include;

	<!- - Include same stylesheets twice, without introducing a cycle. - ->
	<xsl:include href="./../BVTs/./xsl2.inc"/>
	<xsl:include href="xsl2.inc"/>
	<xsl:include href="inc/xsl1.inc"/>

	<!- - Absolute HTTP path - ->
	<xsl:include href="http://webxtest/msxml/msxml40/tests/xslt/bvts/inc/xsl3.inc"/>-->
</xsl:stylesheet>
