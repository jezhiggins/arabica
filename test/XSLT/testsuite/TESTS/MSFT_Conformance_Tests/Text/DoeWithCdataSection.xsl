<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

   <!-- This test is a coverage test case for DCR 53329. 
   -->

   <xsl:output omit-xml-declaration="no" indent="no" encoding="utf-8" />

   <xsl:template match='/'>
	<root>
	  <text>
	   <xsl:text disable-output-escaping='yes'> 
		<![CDATA[ &amp;amp; ]]>
	   </xsl:text>
	  </text>
	  
	  <xsl:apply-templates />
	</root>
   </xsl:template>
	
   <xsl:template match='/root/text'>
	<text>
	   <xsl:value-of disable-output-escaping='yes' select='.' />
	</text>
   </xsl:template>

</xsl:stylesheet>