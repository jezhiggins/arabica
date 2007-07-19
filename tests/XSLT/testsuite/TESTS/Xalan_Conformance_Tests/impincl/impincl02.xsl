<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: IMPINCL02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6 Combining Stylesheets -->
  <!-- Purpose: Included document's xsl:import (f imports g) is moved into the
    including document. Import precedence is (high) impincl02, g (low) -->

<xsl:include href="f.xsl"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="foo"/>
  </out>
</xsl:template>

</xsl:stylesheet>