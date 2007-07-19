<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This a regression test for bug 58698. It validates that if indent is not
	     specified on xsl:output, and method='html' - then indent should be used
	     by default. 
	-->

	<xsl:output omit-xml-declaration="yes" method='html' encoding='utf-8' />

	<xsl:template match="PERIODIC_TABLE">
	  <html>
	    <head><title>The Elements</title></head>
		  <body>
		    <table>
			  <tr><xsl:apply-templates select="ATOM" /></tr>
		    </table>
		  </body>
	    </html>
	</xsl:template>

	<xsl:template match="ATOM">
	  <tr><xsl:apply-templates select="NAME"/></tr>
	</xsl:template>

	<xsl:template match="NAME">
	  <td><xsl:number level="any" /></td>
	  <td><xsl:value-of select="."/></td>
	</xsl:template>
        
</xsl:stylesheet>

