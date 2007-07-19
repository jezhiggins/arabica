<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace36 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: Scott Boag -->
  <!-- Purpose: Test for resetting of the unspecified default namespace by a contained xsl:element. -->

<xsl:template match = "/">
  <out>
    <xsl:element namespace="http://abc" name="foo">
      <xsl:element name="yyy"/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>


