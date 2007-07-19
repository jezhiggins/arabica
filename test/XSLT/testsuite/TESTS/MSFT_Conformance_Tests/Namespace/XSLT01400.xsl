<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform ">
  <xsl:template match="/">
    <span style="color=green">
  Include file with including xslt03001a </span>
          <p/>  
          
          <xsl:for-each select="//book/author">

           <span style="color=blue" ID="test"> <xsl:value-of select="award"/> </span>
          </xsl:for-each>


       
  
  </xsl:template>
<xsl:include href="http://webxtest/testcases/XSLT03001a.xsl"/>
</xsl:stylesheet>