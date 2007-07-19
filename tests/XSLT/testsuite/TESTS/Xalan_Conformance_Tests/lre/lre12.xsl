<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: LRE12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test warning if required element name is null.-->
  <!-- ExpectedException: XSL Warning: Illegal attribute name: -->
  <!-- The above is issued as a warning, then the content is put out as an LRE. -->

<xsl:template match="doc">
  <out>
    <xsl:element name="">
      This should be directly inside the out element.
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>
