<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string128 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of contains() function with two paths, 
       second argument is multiple nodes, first of those nodes does NOT contain the string. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="contains(main,sub)"/>
  </out>
</xsl:template>

</xsl:stylesheet>