<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0" xmlns:my='http://foo.com'>
 
<xsl:output method="my:xml" omit-xml-declaration="yes" indent="yes"/>  
<xsl:template match="/">  
<xsl:copy-of select="/xslTutorial"/>  
</xsl:template>  

</xsl:stylesheet>  
