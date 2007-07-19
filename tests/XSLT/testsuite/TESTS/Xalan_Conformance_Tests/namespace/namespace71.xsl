<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace71 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Baseline case of an xmlns declaration in xsl:element. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="foo" xmlns="">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>


