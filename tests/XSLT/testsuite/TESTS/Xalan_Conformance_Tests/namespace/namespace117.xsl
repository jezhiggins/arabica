<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace117 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Create prefixed attribute with namespace requested via attribute. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:attribute name="bee:see" namespace="http://bee.com">true</xsl:attribute>
  </out>
</xsl:template>

</xsl:stylesheet>