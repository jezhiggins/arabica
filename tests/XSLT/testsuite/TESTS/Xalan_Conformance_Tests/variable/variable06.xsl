<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters  -->
  <!-- Purpose: Set variable by name but no value, should get null string -->
  <!-- Author: Paul Dick -->
  <!-- Note: "If the variable-binding element has empty content and 
              does not have a select attribute, then the value of the 
              variable is an empty string." -->
                
<xsl:template match="doc">
  <xsl:variable name="x"/>
  <out>
    <xsl:value-of select="$x=''"/>
  </out>
</xsl:template>

</xsl:stylesheet>
