<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:output
  method = "xml" 
  version = "1.0" 
  omit-xml-declaration = "no"
  doctype-public = "" 
  doctype-system = "string" 
  cdata-section-elements = "qnames" 
  indent = "yes" 
  media-type = "string" /> 
<xsl:output doctype-system = "second string"/>

<xsl:template match="/">  
COPY-OF:
<xsl:copy-of select="/xslTutorial"/>  
GET TEXT:
<xsl:apply-templates select="//SELECT"/>
</xsl:template>  
<xsl:template match="//SELECT">

</xsl:template>
</xsl:stylesheet>  
