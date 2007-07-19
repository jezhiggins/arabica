<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH08 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.5 -->
  <!-- Purpose: Test of '-' operator.  Note since XML allows "-" in names
       the "-" operator typically needs to be preceded by whitespace.-->



<xsl:variable name="h" select="60"/>
<xsl:variable name="i" select="20"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="3-1"/><xsl:text>,</xsl:text>
	<xsl:value-of select="$h - $i"/> 
  </out>
</xsl:template>
 
</xsl:stylesheet>
