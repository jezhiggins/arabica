<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<html>
		<b:root xmlns:b="a">
			<xsl:attribute name="att">xyz</xsl:attribute>
	    </b:root>
	</html>
</xsl:template>

</xsl:stylesheet>