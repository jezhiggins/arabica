<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: mdocs10 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test document() function with local file specification. -->

<xsl:template match="doc">
  <out>
    <xsl:copy-of select='document("../impincl-test/mdocstest.xml")//b'/><xsl:text>
</xsl:text>
    <xsl:copy-of select='document("../impincl-test/mdocstest.xml")//a'/>
  </out>
</xsl:template>

</xsl:stylesheet>