<xsl:stylesheet version="1.5" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="unknown">
	<!--This never matches so it doesn't really matter if there are any XSLT Elements that are not supposed to be inside a template.-->
	<xsl:include href="fcp.xsl"/>
</xsl:template>

<xsl:template match="text()"/>


</xsl:stylesheet>



