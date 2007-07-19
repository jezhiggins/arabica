<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href="84615a.xsl"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="bookstore">
    <span style="color=green"><br/>
  Include file with dtd (transformed stylesheet in green, included in black, if magazine titles from included template are wrapped in a span with style=red transform was done in the wrong order) </span>
          <p/>  
          
          <xsl:for-each select="//book/author">

           <span style="color=green" ID="test"> <xsl:value-of select="award"/> </span><br/>
          </xsl:for-each>

<span style="color:red">
       <xsl:apply-templates/>
</span>
  </xsl:template>



<xsl:template match="*">
</xsl:template>

</xsl:stylesheet>