<?xml version="1.0"?>
<xsl:stylesheet
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
   xmlns:err="http://www.error.com">

  <!-- FileName: namespace48 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 -->
  <!-- Creator: David Marston -->
  <!-- Discretionary: name="element-name-not-QName" choice="pass-through" -->
  <!-- Purpose: Test for error recovery when assigned name ends with : (has null local-part) -->

<xsl:template match = "doc">
  <out>
    <xsl:element name="err:">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>