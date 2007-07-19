<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<!-- error case, invalid namespace URI -->

<xsl:template match="/">
	<html>
        <root xmlns="a" >
			<xsl:attribute name="x" namespace="b" >abc</xsl:attribute>
		</root>
	</html>
</xsl:template>

</xsl:stylesheet>

