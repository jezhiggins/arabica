<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:include href="http://webxtest/testcases/XSLT03014a.xsl"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
<xsl:variable name="a" select="//book/author/lastname[0]"/>
  <xsl:template match="/">
    <span style="color=green">
  This text is from the main stylesheet. 
          <p/>  
         value of param: <xsl:value-of select="$d"/>
          
</span>

  
  </xsl:template>


</xsl:stylesheet>
