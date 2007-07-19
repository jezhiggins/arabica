<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <!-- encoding set to cp1252-->
    <xsl:output method="text" encoding="cpFoo"/>

	<xsl:template match="/">  
	<xsl:copy-of select="//xslTutorial"/>  
	</xsl:template>  
</xsl:stylesheet>
