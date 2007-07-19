<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:foo="http://aaa">

  <!-- FileName: namespace25 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Simple case of creating LRE with nested namespace declarations. -->

<xsl:template match="/">
    <foo:stuff xmlns:foo="http://bbb">
      <foo:stuff xmlns:foo="http://ccc"/>
    </foo:stuff>
</xsl:template>

</xsl:stylesheet>


