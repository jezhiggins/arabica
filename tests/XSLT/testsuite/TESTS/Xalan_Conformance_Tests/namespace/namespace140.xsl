<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:someprefix="http://someURI">

  <!-- FileName: namespace140 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Santiago Pericas-Geertsen -->
  <!-- Purpose: Check for AVT on element name when xsl:element has namespace attribute. -->

<xsl:output method="xml" indent="yes" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <!-- Name is literal, no prefix, no namespace: see copy18 -->
    <!-- Name is literal, no prefix, namespace: see namespace36 -->
    <!-- Name is literal, prefix, no namespace: see namespace40  -->
    <!-- Name is literal, prefix, namespace: see namespace56 -->

    <!-- Name is AVT, no prefix, no namespace -->
    <xsl:element name="{noprefix}"/>

    <!-- Name is AVT, no prefix, namespace -->
    <xsl:element name="{noprefix}" namespace="http://literalURI"/>

    <!-- Name is AVT, prefix, no namespace -->
    <xsl:element name="{prefix}"/>
    <!-- It's just a string in the source tree, but prefix must be declared here in the stylesheet! -->

    <!-- Name is AVT, prefix, namespace -->
    <xsl:element name="{prefix}" namespace="http://literalURI"/>
  </out>
</xsl:template>

</xsl:stylesheet>