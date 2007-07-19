<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href="91148/91148.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:variable name="X" select="//book/author/lastname[0]"/>
  <xsl:template match="/" priority="1">
    <span style="color=red">
	This text is from the main stylesheet. </span>
    <p/>  
          
    <xsl:for-each select="//book/author">

    <span style="color=red" ID="test"> <xsl:value-of select="award"/> </span>
    </xsl:for-each>      
  
  </xsl:template>
</xsl:stylesheet>
