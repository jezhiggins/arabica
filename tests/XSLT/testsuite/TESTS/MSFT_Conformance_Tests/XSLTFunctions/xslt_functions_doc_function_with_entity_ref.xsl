<!DOCTYPE xsl:stylesheet [
<!ENTITY inc-doc SYSTEM "./inc/test.ent">
]>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output encoding="UTF-8" indent="yes"/>

	<xsl:template match="/">
		&inc-doc;
		<xsl:copy-of select="document(document('')//inc-doc)"/>
	</xsl:template>
</xsl:stylesheet>


