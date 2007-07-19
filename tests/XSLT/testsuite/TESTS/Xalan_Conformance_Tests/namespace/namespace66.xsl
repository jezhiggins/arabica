<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace66 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test resetting of a prefix to same URI as known prefix. -->

<xsl:template match = "/">
  <out xmlns:p1="http://xyz">
    <xsl:element namespace="http://xyz" name="baz:foo">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>


