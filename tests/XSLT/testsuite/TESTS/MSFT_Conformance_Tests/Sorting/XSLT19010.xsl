<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
Sort first by title as text then by price as number
<xsl:for-each select="bookstore/book">  
<xsl:sort data-type="text" select="title"/>  
<xsl:sort data-type="number" select="price"/> 
 <xsl:value-of select="title"/>   <xsl:value-of select="price"/>
</xsl:for-each>  

</xsl:template>  
</xsl:stylesheet>  


