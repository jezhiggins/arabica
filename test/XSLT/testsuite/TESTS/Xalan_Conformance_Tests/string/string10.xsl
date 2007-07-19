<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str10 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Test of 'normalize-space()' function  -->

<xsl:template match="/doc">
   <out>
      <xsl:value-of select="normalize-space('&#9;&#10;&#13; 
      ab    
      cd&#9;&#10;&#13;
      ef&#9;&#10;&#13; ')"/><xsl:text>&#10;</xsl:text>
	  <xsl:value-of select="normalize-space(a)"/>
   </out>
</xsl:template>
 
</xsl:stylesheet>
