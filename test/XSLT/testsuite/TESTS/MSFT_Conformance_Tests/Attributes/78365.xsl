<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<!-- error case, invalid namespace URI -->
<xsl:template match="/">

	<html>
		<root>
		<xsl:attribute name="a" namespace="&lt; &gt; &apos; &quot;a     - - &#13;  -
-&amp;             ">&lt;&gt;&apos;&quot;&amp;    - &#10; -

end
		</xsl:attribute >
		</root>
	</html>

</xsl:template>
</xsl:stylesheet>



