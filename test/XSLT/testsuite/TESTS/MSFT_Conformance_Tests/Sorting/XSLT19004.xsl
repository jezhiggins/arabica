<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
 Sort by number where one number has a datatype="string"
<xsl:for-each select="bookstore/book">  
<xsl:sort data-type="number" select="number"/>  

 <xsl:value-of select="title"/>   <xsl:value-of select="number"/>
</xsl:for-each>  

</xsl:template>  
</xsl:stylesheet>  


