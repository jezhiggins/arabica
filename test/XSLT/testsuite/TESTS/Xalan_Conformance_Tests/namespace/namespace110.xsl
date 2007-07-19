<?xml version="1.0"?>
<xsl:stylesheet
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace110 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for invalid namespace URI; spec says "not syntactically legal URI" is NOT error. -->

<xsl:template match = "doc">
  <out>
    <xsl:element name="ouch:foo" xmlns:ouch="&quot;">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>