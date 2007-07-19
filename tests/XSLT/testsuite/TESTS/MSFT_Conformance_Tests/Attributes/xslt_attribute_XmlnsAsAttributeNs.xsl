<?xml version='1.0'?>

<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version='1.0'>

   <xsl:output omit-xml-declaration='yes' encoding='utf-8' indent='no' />

   <xsl:template match='/'>
	<cat>
	<xsl:attribute name="foobar" namespace="http://www.w3.org/2000/xmlns/">
		dog
	</xsl:attribute>
	</cat>
   </xsl:template>

</xsl:stylesheet>