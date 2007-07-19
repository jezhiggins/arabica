<?xml version="1.0"?>

<xsl:stylesheet version= '1.0' 
	xmlns:xsl='http://www.w3.org/1999/XSL/Transform' 
	xmlns:foo="urn-user"
	exclude-result-prefixes="foo">  
 
	<!-- This stylesheet is a regression test case for bug 65665. It validates
	     that the stylesheet is not removing the prefix use from the included
             stylesheet -->

	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match="/">  
		<literal>
		text
		</literal>
		<xsl:apply-templates />
	</xsl:template>  

	<xsl:include href="xslt_include_ImplicitExclusionChildNsPrefix2.xsl" />

</xsl:stylesheet>  
