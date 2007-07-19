<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 
 
<xsl:template match="/">  
<!-- Lesson. Note how the initial context node  
is reduced by the apply templates; this stops  
the 'leaking' of content when all I want is  
a subset of the whole in the result tree -->  
<xsl:apply-templates select="//me"/>  
</xsl:template>  
 
 
<xsl:template match="br">  
<br />  
</xsl:template>  
 
<xsl:template match="me" priority="10">  
<html>  
<head>  
 
<title> <xsl:text> Document</xsl:text> </title>  
</head>  
<body>  
 
 

 
<H2>Descendant or Self Axis</H2>  
<b><xsl:apply-templates select="descendant-or-self::*/p"/></b>  
 
<H2>Descendant Axis</H2>  
<b><xsl:apply-templates select="descendant::*/p"/></b>  
 
<H2>Self Axis</H2>  
<b><xsl:apply-templates select="self::*/p"/></b>  
 
<H2>Child Axis</H2>  
<b><xsl:apply-templates select="child::*/p"/></b>  
 

 
 
 
 
 
 
 
<H2>Attribute Axis</H2>  
<b><xsl:apply-templates select="attribute::*"/></b>  
 
<H2>Parent Axis</H2>  
<b><xsl:apply-templates select="parent::*/p"/></b>  
 
<H2>Ancestor or Self Axis</H2>  
<b><xsl:apply-templates select="ancestor-or-self::*/p"/></b>  
 
<H2>Ancestor Axis</H2>  
<b><xsl:apply-templates select="ancestor::*/p"/></b>  
 
 
 <H2>value of .</H2>  
<b><xsl:value-of select="."/></b>  
 
  <H2>value of ..</H2>  
<b><xsl:value-of select=".."/></b> 

</body>  
</html>  
 
</xsl:template>  
 
 
</xsl:stylesheet>  

