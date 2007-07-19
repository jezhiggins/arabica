<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
>  
 
<xsl:output
  method = "xml" 
  version = "1.0" 
  omit-xml-declaration = "no"
  cdata-section-elements = "cdata1" 
  indent = "yes"/> 


<xsl:template match="/">  

<cdata1>bar</cdata1>
text
<cdata1/>


</xsl:template>
</xsl:stylesheet>  
