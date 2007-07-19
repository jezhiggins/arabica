<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml"/>

  <!-- FileName: variable24 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 Values of Variables and Parameters -->
  <!-- Purpose: Test the ability of variable to hold the result of document() -->
  <!-- Author: Paul Dick -->

<xsl:template match="doc">
  <out>
    <xsl:variable name="document-nodelist" select="document('variable20.xml')"/>
    <xsl:copy-of select="$document-nodelist"/>
  </out>
</xsl:template>

</xsl:stylesheet>
