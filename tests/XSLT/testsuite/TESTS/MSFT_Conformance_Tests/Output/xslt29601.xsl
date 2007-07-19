<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
 
<xsl:output method="xml" doctype-public="string" 
doctype-system="string"  cdata-section-elements="qnames"
  media-type = "string" foo="foo" indent="yes"/>  
<xsl:template match="/">  
<xsl:copy-of select="/"/>  
</xsl:template>  

</xsl:stylesheet>  
