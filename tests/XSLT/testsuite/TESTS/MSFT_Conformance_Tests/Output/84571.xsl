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
<cdata1>bar</cdata1>
text
<cdata1/>

<cdata2>bar2</cdata2>
text2
<cdata2/>

<foo:cdata3>bar3</foo:cdata3>
text3
<foo:cdata3/>

<cdata4>bar4</cdata4>
</output>
</xsl:template>
</xsl:stylesheet>  
