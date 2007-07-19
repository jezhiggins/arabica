<!-- This is a test case for bug # 70882 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output encoding="UTF-8" indent="yes"/>


    	<xsl:template match="root">
	<xsl:copy use-attribute-sets="simple"/>
    	</xsl:template>


	<xsl:attribute-set name="simple">
        	<?my-pi test for comments?>
		<xsl:attribute name = "test"><xsl:value-of select="."/></xsl:attribute>
    	</xsl:attribute-set>

</xsl:stylesheet>