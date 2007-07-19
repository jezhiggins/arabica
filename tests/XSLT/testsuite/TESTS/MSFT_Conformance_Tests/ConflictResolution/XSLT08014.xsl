<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


  <xsl:template match="bookstore/book">
    
          
          <xsl:apply-templates select="author"/>
	
           <xsl:apply-templates select="author/last-name"/>

	
          

		

 </xsl:template>

 <xsl:template match="author" priority="2">
- <SPAN style="color=green"> <xsl:value-of select="my:country" /> </SPAN>
  </xsl:template>
 <xsl:template match="last-name" priority="1.22">
- <SPAN style="color=green">  <xsl:value-of select="." />   </SPAN>
  </xsl:template>
 <xsl:template match="last-name" priority="#A">
- <SPAN style="color=red" ID="test">
  <xsl:value-of select="." /> 
  </SPAN>
  </xsl:template>
 

 <xsl:template match="author" priority="22">
- <SPAN style="color=red" ID="test">
  <xsl:value-of select="my:country" /> 
  </SPAN>
  </xsl:template>

 <xsl:template match="*" priority="-5">
	<xsl:apply-templates select="*"/>
 </xsl:template>



</xsl:stylesheet>
