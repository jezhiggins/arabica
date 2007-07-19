<?xml version="1.0"?>  

<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  

  <!-- This stylesheet is a regression test case for bug 65748. It validates that an output
       text of &amp; is not output to strictly '&' in the result document, since it is
       a reserved XML character. It should be output to the ampersand character entity. -->
 
  <xsl:output method="xml" omit-xml-declaration="yes" />  

  <xsl:template match="/">  
    <area checked="&amp;"/> 
  </xsl:template>

</xsl:stylesheet>  
