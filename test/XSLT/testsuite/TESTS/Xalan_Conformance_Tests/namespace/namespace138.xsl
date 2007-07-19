<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:n="http://ns.test.com">

  <!-- FileName: namespace138 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for resetting of a namespace prefix by copy-of. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match = "/">
  <out>
    <xsl:text>
</xsl:text>
    <n:x>from stylesheet</n:x>
    <xsl:text>
</xsl:text>
    <xsl:element name="e" namespace="http://literalURI">
      <xsl:copy-of select="doc/*"/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>