<?xml version='1.0'?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
	xmlns:foo='http://www.w3.org/2000/xmlns/'
	>

   <xsl:output omit-xml-declaration='yes' encoding='utf-8' indent='no' />

   <xsl:template match='/'>
	<xsl:element name='foo:bar'>
		dog
	</xsl:element>
   </xsl:template>

</xsl:stylesheet>