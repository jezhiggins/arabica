<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:p1="http://testguys.com">

  <!-- FileName: namespace97 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for prefixed name when prefixed NS is in scope; also set default locally. -->
  <!-- NOTE: Processor developers could legitimately disagree about where the default name
     has to be set in the result. It must be in effect for yyy, but could be for foo
     as well. The spec doesn't address this point. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="p1:foo" xmlns="http://other.com">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>