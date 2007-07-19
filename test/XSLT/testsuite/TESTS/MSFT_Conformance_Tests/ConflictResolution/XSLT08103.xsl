<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"><xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


 

 <xsl:template match="processing-instruction()">
- <SPAN style="color=green"><xsl:value-of select="."/> </SPAN>
  </xsl:template>
 <xsl:template match="processing-instruction()" priority="-0.10">
- <SPAN style="color=red"><xsl:value-of select="." /> </SPAN>
  </xsl:template>
 
<xsl:template match="*" priority="-.00000001">

</xsl:template>


</xsl:stylesheet>
