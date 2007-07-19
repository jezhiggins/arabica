<?xml version="1.0"?>
<xsl:stylesheet
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace106 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test recovery when assigned name begins with : (has null namespace) -->

<xsl:template match = "doc">
  <out>
    <xsl:element name=":foo">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>