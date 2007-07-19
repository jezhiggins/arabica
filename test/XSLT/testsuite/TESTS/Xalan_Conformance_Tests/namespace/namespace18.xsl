<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test exclude-result-prefixes, attribute level -->

<xsl:template match="/">
  <out xmlns:anamespace="http://foo.com"  xsl:exclude-result-prefixes="anamespace">
    <p>
      <xsl:attribute name="test" namespace="http://foo2.com">true</xsl:attribute>
    </p>
  </out>
</xsl:template>

</xsl:stylesheet>
