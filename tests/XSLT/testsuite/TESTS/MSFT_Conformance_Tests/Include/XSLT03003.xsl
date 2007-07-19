<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    <span style="color=green">
  Include file with including nonexistant xslt03003a </span>
          <p/>  
          
          <xsl:for-each select="//book/author">

           <span style="color=blue" ID="test"> <xsl:value-of select="award"/> </span>
          </xsl:for-each>


       
  
  </xsl:template>
<xsl:include href="http://webxtest/msxml/msxml40/tests/xslt/include/XSLT03003a.xsl"/>
</xsl:stylesheet>
