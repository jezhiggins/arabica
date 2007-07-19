<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting - level = "single" -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/02/2000 -->

	<xsl:template match="PERIODIC_TABLE">
	  <html>
	    <head><title>The Elements</title></head>
		  <body>
		    <table>
			  <tr><xsl:apply-templates select="ATOM"/></tr>
			</table>
		  </body>
	    </html>
	</xsl:template>

	<xsl:template match="ATOM">
	  <tr><xsl:apply-templates select="NAME"/></tr>
	</xsl:template>

	<xsl:template match="NAME">
	  <td><xsl:number level = "single"/></td>
	  <td><xsl:value-of select="."/></td>
	</xsl:template>


        
</xsl:stylesheet>

