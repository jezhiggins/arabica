<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace72 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Put both an unprefixed xmlns declaration and namespace attrib in xsl:element. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="foo" namespace="http://zebie" xmlns="">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>


