<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 

<xsl:variable name = "variable1">1234.78</xsl:variable>
<xsl:param name = "param1">#,###.00</xsl:param>

<xsl:template match="/">
 <out>
   <xsl:value-of select = "format-number($variable1,$param1)"/>
 </out>
</xsl:template>

</xsl:stylesheet>