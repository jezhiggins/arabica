<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


 <xsl:template match="bookstore" priority="1">
    <span style="color=red">
  1 first award in doc order </span>
          <p/>  
          
          <xsl:for-each select="book/author">

           <span> <xsl:value-of select="award"/> </span><br/>
          </xsl:for-each>

<span style="color:blue">
       <xsl:apply-templates/>
</span>
</xsl:template>

 <xsl:template match="bookstore" priority="1">
   <br/> <span style="color=green">
  1 second award in doc order </span>
          <p/>  
          
          <xsl:for-each select="book/author">

           <span> <xsl:value-of select="award"/> </span><br/>
          </xsl:for-each>

<span style="color:blue">
       <xsl:apply-templates/>
</span>
  </xsl:template>


<xsl:template match="/" priority="1">
<xsl:for-each select="//magazine/title">
<br/><span style="color:red">1 first title in doc order</span>
            <xsl:value-of select="."/> 
          </xsl:for-each>


<span style="color:red">
<xsl:apply-templates/>
</span>
</xsl:template>
 
<xsl:template match="/" priority="1">
<xsl:for-each select="//magazine/title">
<br/><span style="color:green">1 second title in doc order</span>
            <xsl:value-of select="."/> 
          </xsl:for-each>

<xsl:apply-templates/>

</xsl:template> 


<xsl:template match="*">

</xsl:template>

</xsl:stylesheet>
