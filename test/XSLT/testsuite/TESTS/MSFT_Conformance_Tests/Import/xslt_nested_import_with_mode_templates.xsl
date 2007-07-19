<!-- Test case for bug # 70863 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:import href="xslt_nested_import_with_mode_templates.inc"/>

	<xsl:template match="/" mode="css">
		<xsl:apply-imports/>
	</xsl:template>

</xsl:stylesheet>