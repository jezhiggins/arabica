<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"> 

  <xsl:template match="/">
 	 <xsl:value-of select="/bookstore/book/author/first-name"/>
  </xsl:template>
   
</xsl:stylesheet>  
