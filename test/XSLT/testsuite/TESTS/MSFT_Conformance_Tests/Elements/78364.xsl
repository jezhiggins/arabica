<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

	<!-- error case, invalid namespace URI -->

	<root>
		<xsl:element name="a" namespace="a     - -  &amp;
'  c      b" >
		</xsl:element>
	</root>
</html>
