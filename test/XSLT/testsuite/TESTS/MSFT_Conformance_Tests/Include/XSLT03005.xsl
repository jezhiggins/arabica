<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    <span style="color=red">
  This text is from the main stylesheet. </span>
          <p/>  
          
          <xsl:for-each select="//book/author">

           <span style="color=red" ID="test"> <xsl:value-of select="award"/> </span>
          </xsl:for-each>


       
  
  </xsl:template>
<xsl:include href="XSLT03005a.xsl"/>
</xsl:stylesheet>
