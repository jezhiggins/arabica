<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace55 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Prefixed xmlns declaration and same-prefixed name; namespace matches default set locally. -->
  <!-- NOTE: Processor developers could legitimately disagree about where the default name
     has to be reset in the result. It must be in effect for yyy, but could be for foo
     as well. The spec doesn't address this point.
     On the other hand, p2 must be set to "barz.com" for the yyy element. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="p2:foo" namespace="http://other.com" xmlns="http://other.com" xmlns:p2="http://barz.com">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>