<xsl:stylesheet version='1.0'
xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>

<xsl:output method="html" indent="no"/>

<xsl:template match="root">
<html>
  <table>
	<tr>
		<td>Test</td>
		<td><xsl:value-of select="."/></td>
	</tr>
 </table>
</html>
</xsl:template>
</xsl:stylesheet>