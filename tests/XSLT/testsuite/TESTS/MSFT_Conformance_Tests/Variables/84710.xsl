<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- A binding shadow is not allowed.  Processor must raise error. -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->

<xsl:template name="sales_tax">
	<xsl:param name="x" select="1"/>
	<xsl:variable name="x" select="2"/>
</xsl:template>

</xsl:stylesheet>