<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<xsl:decimal-format name="foo" 
		infinity="~" 
		minus-sign="+" />
	
	<xsl:template match="/">
	<test name="non-default">infinity =<xsl:value-of select="format-number(-1 div 0, '0', 'foo')"/></test>
	</xsl:template>

</xsl:stylesheet>