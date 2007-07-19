<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns="http://testguys.com" xmlns:ped="http://www.test.com">

  <!-- FileName: namespace109 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use namespace attribute, but namespace new at that point; default was set. -->
  <!-- Requested name has no prefix, and we can get by without it. -->

<xsl:template match="doc">
  <out>
    <xsl:element name="inner" namespace="http://other.com">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>
