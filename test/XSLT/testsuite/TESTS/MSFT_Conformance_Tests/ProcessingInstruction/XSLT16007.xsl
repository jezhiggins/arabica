<?xml version="1.0" ?>
<!DOCTYPE xsl:stylesheet SYSTEM "http://webxtest/testcases/stylesheet.dtd" [
	<!ATTLIST xsl:processing-instruction
		xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform"
		version CDATA #IMPLIED
		CORNHOLIO	CDATA	"Beavis"
		Itchy		CDATA	#IMPLIED
		name		CDATA	"bob" >

]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/">

<xsl:processing-instruction xmlns:xsl="http://www.w3.org/1999/XSL/Transform">...</xsl:processing-instruction>

</xsl:template>
</xsl:stylesheet>
