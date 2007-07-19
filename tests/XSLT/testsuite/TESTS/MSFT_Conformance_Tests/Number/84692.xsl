<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- Number Formatting - format = "a.a.a" | "A.A.A" | "1.1.1" | "i.i.i" |" I.I.I" | "@1I@A" | "1*I*A" | "1>a?i" -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/04/2000 -->


	<xsl:template match="/">  
		<TABLE BORDER="1">  
		  <xsl:for-each select="//chapter">
			<TR>
			  <TD><xsl:number level="multiple" format = "a.a.A" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "a.A.A" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "1.1.1" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "i.i.i" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "I.I.I" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "@1I@A" letter-value="traditional"/></TD>
			  <TD><xsl:number level="multiple" format = "1*I*A" letter-value="traditional"/></TD>	
			  <TD><xsl:number level="multiple" format = "1>a?i" letter-value="traditional"/></TD>
			  <TD><xsl:value-of select="./text()"/></TD>
			</TR>  
		  </xsl:for-each>  
		</TABLE>  
	</xsl:template>  
</xsl:stylesheet>  

