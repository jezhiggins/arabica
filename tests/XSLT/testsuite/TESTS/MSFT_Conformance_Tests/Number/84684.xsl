<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting - count -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/04/2000 -->

	<xsl:template match="/">  
		<TABLE BORDER="1">  
		  <TR>
		    <TH>Number</TH>
		    <TH>text</TH>
		  </TR>  
		  <xsl:for-each select="//chapter|//section|//subsection">
			
			<TR>
			  <TD><xsl:number count="section"/></TD>
			  <TD><xsl:value-of select="name"/></TD>
			</TR>  
		  </xsl:for-each>  
		</TABLE>  
	</xsl:template>  
</xsl:stylesheet>  

