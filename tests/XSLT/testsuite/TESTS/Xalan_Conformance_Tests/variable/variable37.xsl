<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable37 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters -->
  <!-- Purpose: Set a variable to a boolean, and show it being used in xsl:if -->
  <!-- Author: David Marston -->

<xsl:template match="doc">
  <xsl:variable name="partest" select="contains('foo','o')"/>
  <out>
    <xsl:if test="$partest">
      <xsl:text>Success</xsl:text>
    </xsl:if>
  </out>
</xsl:template>

</xsl:stylesheet>
