<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:template match="/xslTutorial/*">  
  	a<xsl:text> </xsl:text>a  
</xsl:template>  

<xsl:template match="text()"/>

</xsl:stylesheet>  