<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

  <xsl:template match="/">
    <span style="color=red">
  Include file with including shift-jis encoded stylesheet </span>
          <p/>  
          
          <xsl:for-each select="//book/author">

           <span style="color=red" ID="test"> <xsl:value-of select="award"/> </span>
          </xsl:for-each>


       
  
  </xsl:template>

<xsl:include href="XSLT03022a.xsl"/>
</xsl:stylesheet>
