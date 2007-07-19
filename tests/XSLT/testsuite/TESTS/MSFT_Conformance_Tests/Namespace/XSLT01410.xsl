<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:template match="p">  
<DIV><B> copy-of :  </B>  
<xsl:copy-of select="."/>  
</DIV>  
<DIV><B> copy :  </B>  
<xsl:copy/>  
</DIV>  
<DIV><B> value-of :  </B>  
<xsl:value-of select="."/>  
</DIV>  
</xsl:template>  
</xsl:stylesheet>  


