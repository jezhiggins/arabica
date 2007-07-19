<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Basic test of applying namespaces to elements. -->

<xsl:output method="xml" encoding="UTF-8" indent="yes" />

<xsl:template match="/">
  <out xmlns:anamespace="http://foo.com">
    <xsl:element name="test" namespace="http://foo.com">
      <inner/>
    </xsl:element>
    <later/>
    <anamespace:anelement/>
  </out>
</xsl:template>

</xsl:stylesheet>