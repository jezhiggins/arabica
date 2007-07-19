<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Set top-level xsl:variable to a string -->
  <!-- Author: Paul Dick -->

<xsl:variable name="ExpressionTest" select="'ABC'"/>

<xsl:template match="doc">
   <out>
      <xsl:value-of select="$ExpressionTest"/>
   </out>
</xsl:template>

</xsl:stylesheet>