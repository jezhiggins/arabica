<?xml version="1.0"?>
<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  

  <!-- This stylesheet is regression test case for bug 66561. It validates that two
	ampersands place next to each as entity elements, and then output using the 
	method html are not escaped by the XSL transformer. -->

  <xsl:output method="html" indent='no' />

  <xsl:template match="/">  
    <html>
    <body>
    <div checked="&amp;&amp;">text</div>
    </body>
    </html>
  </xsl:template>

</xsl:stylesheet>  
