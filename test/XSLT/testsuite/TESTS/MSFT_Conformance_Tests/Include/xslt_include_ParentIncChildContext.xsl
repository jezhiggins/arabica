<?xml version="1.0"?>

<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' xmlns:foo="urn-user">  
 
	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match="/">  
		<literal />
		text
		<xsl:apply-templates />
	</xsl:template>  

	<xsl:include href="xslt_include_ParentIncChildContext2.xsl" />

</xsl:stylesheet>  
