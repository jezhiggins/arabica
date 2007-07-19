<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
xmlns:foo="bar">  
 
<xsl:output
  method = "xml" 
  version = "1.0" 
  omit-xml-declaration = "no"
  cdata-section-elements = "cdata1" 
  indent = "yes"/> 
<xsl:output cdata-section-elements = "cdata2"/>
<xsl:output cdata-section-elements = "foo:cdata3"/>

<xsl:template match="/">  
<output>
<cdata1>
<xsl:value-of select="//xslTutorial/SELECT[2]"/>
</cdata1>
text
<cdata1>text</cdata1>

</output>
</xsl:template>
</xsl:stylesheet>  
