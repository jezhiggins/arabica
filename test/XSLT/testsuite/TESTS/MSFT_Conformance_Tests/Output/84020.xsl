<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <!-- encoding set to shift-jis-->
    <xsl:output method="text" encoding="shift-jis"/>

	<xsl:template match="/">  
	<xsl:copy-of select="//xslTutorial"/>  
	</xsl:template>  
</xsl:stylesheet>
