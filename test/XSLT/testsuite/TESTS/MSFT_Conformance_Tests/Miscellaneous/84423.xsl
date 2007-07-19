<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' > 
  
 
<xsl:template match="/">  
 
<TABLE border='1' width="90%">  
<TR><TH>Element</TH><TH>Occurs</TH></TR>  
<xsl:for-each select="/descendant::*">  
<xsl:variable name="pos" select="position()"/>  
<xsl:if test="not(/descendant::*[position() &lt; $pos and name()=name(current())])">  
<TR><TD><xsl:value-of select="name()"/></TD><TD>  
<xsl:value-of select="count(/descendant::*[name()=name(current())])"/>  
</TD></TR>  
</xsl:if>  
</xsl:for-each>  
<TR><TH>Total count</TH><TH><xsl:value-of select="count(//*)"/></TH></TR>  
</TABLE>  
</xsl:template>  
</xsl:stylesheet>  

