<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  
 

<xsl:template match="/">  
<xsl:if test="//DOCUMENT[TAG1 = TAG2]">  
<xsl:value-of select="//DOCUMENT/TAG1"/>  
</xsl:if>  
<BR/>  
<xsl:if test="//DOCUMENT[TAG3 = TAG4/TAG5]">  
<xsl:value-of select="//TAG4/text()"/>  
</xsl:if>  
</xsl:template>  
</xsl:stylesheet>  


