<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl27 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6.2 -->
  <!-- Creator: Morris Kwan -->
  <!-- Purpose: href is a URI containing the "file:" scheme part. -->

<xsl:import href="file:fragments/imp27b.xsl"/>

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="doc" />
  </out>
</xsl:template>

</xsl:stylesheet>
