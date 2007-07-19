<?xml version="1.0" ?>
<!DOCTYPE xsl:stylesheet SYSTEM "stylesheet.dtd" [
	<!ATTLIST xsl:apply-templates	bungholio CDATA "beavis"
					senator	CDATA	"Bob Packwood"
					CEO	CDATA	"William H. Gates III" >

]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/">
	<xsl:apply-templates select="//*" />
</xsl:template>

<xsl:template match="xsl:template">true</xsl:template>

</xsl:stylesheet>