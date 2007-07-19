<?xml version="1.0" ?>
<!DOCTYPE xsl:stylesheet SYSTEM "stylesheet.dtd" [
	<!ATTLIST xsl:attribute	name CDATA	"name" >

]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" />
	<xsl:template match="/">
		<xsl:element name="Guy"><xsl:attribute>bob</xsl:attribute></xsl:element>
	</xsl:template>
</xsl:stylesheet>