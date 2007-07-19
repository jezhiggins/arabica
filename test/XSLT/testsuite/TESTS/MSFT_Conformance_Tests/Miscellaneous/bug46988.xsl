
<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 


<xsl:template match="p">   <![CDATA[]]> 
<DIV><B><xsl:text> copy-of : </xsl:text> </B>  
<xsl:copy-of select="."/>  
</DIV>  
<DIV><B><xsl:text> copy : </xsl:text> </B>  
<xsl:copy/>  
</DIV>    <![CDATA[]]>
<DIV><B><xsl:text> value-of : </xsl:text> </B>  
<xsl:value-of select="."/>    <![CDATA[]]>
</DIV>  
</xsl:template>    <![CDATA[]]>
</xsl:stylesheet>  
