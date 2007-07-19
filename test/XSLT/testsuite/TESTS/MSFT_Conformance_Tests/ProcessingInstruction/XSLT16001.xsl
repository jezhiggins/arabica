<?xml version="1.0" ?>
<!DOCTYPE xsl:stylesheet SYSTEM "http://webxtest/testcases/stylesheet.dtd" [
	<!ATTLIST xsl:template xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">	
	<!ATTLIST xsl:processing-instruction xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">
	<!ATTLIST xsl:processing-instruction name CDATA "test" >
	]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	
<xsl:template match="/">
BEFORE
<xsl:processing-instruction />
AFTER
</xsl:template>
</xsl:stylesheet>

