<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="sorttest">
    
   

<B>
<xsl:apply-templates select="elem1"/>
</B>  
 
</xsl:template>  

  
<xsl:template match="elem1">  
<SPAN>  
          <xsl:for-each select="*">
		<xsl:sort select="." order="descending"/>
		<xsl:sort select="@x" order="ascending"/>
		<xsl:sort select="@y" order="descending"/>
		<xsl:sort select="@z" order="ascending"/>
<hr/>
<xsl:value-of select="name()"/> 
 is a ordered first by descending <value-of select="."/> then by ascending x: <value-of select="elem1a\@x"/> then by descending y:<value-of select="elem1a\@y"/> then by ascending z: <value-of select="elem1a\@z"/>

         </xsl:for-each> 
	    
   </SPAN>
  </xsl:template>
</xsl:stylesheet>

