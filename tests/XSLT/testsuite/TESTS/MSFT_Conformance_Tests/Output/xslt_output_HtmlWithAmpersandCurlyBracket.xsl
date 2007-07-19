<?xml version="1.0"?>

<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
  <!-- This stylesheet is a regression test case for bug 66562. It validates
       that the ampersand, when placed before an open-curly-bracket, is not
       escaped (when the output method equals html) in the resulting output document. -->

  <xsl:output method="html" indent='no'/>  

  <xsl:template match="/">  
    <html>
      <body>
        <area checked="&amp;{{foo}}">foo</area>
      </body>
    </html>
  </xsl:template>

</xsl:stylesheet>  
