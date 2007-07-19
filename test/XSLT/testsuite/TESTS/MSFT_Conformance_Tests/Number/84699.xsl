<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- XSLT: Number formatting - value attribute - format = "a" | "A" | "1" | "I" | "I" | "I.I.a.A" | "@a" | "*1A" | "  1> " -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 04/05/2000 -->

<xsl:template match="/">  
	<TABLE>  
		<xsl:for-each select="//n">  
			<TR><TD>  
				<TD>format = "a" -><xsl:number value="position()" format = "a" letter-value="traditional"/> |</TD>
				<TD>format = "A" -> <xsl:number value="position()" format = "A" letter-value="traditional"/> | </TD>
				<TD>format = "1" -> <xsl:number value="position()" format = "1" letter-value="traditional"/> | </TD>
				<TD>format = "i" -> <xsl:number value="position()" format = "i" letter-value="traditional"/> | </TD>
				<TD>format = "i.I.a.A" -> <xsl:number value="position()" format = "i.I.a.A" letter-value="traditional"/> | </TD>
				<TD>format = "@a" -> <xsl:number value="position()" format = "@a" letter-value="traditional"/> | </TD>
				<TD>format = "*1A" -> <xsl:number value="position()" format = "*1A" letter-value="traditional"/> | </TD>	
				<TD>format = " 1> " -> <xsl:number value="position()" format = " 1> " letter-value="traditional"/> | </TD>
			</TD></TR>  
		</xsl:for-each>  
	</TABLE>  
</xsl:template>  

</xsl:stylesheet>  
