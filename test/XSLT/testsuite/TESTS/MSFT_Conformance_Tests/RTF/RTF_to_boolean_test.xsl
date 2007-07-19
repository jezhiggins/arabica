<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:variable name="RTF">Some text</xsl:variable>

<xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>
    
    <xsl:template match="/">
     	<out>
		<xsl:if test="$RTF">True</xsl:if>
	</out>
    </xsl:template>

</xsl:stylesheet>