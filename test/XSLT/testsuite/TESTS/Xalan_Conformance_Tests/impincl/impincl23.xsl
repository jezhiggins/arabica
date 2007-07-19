<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl23 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6 Combining Stylesheets -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Included document's xsl:import (i23incl imports i23sub) is moved into the
    including document. Import precedence for templates matching foo is
    (high) i23sub, h (low) -->

<xsl:import href="h.xsl"/>
<xsl:include href="fragments/i23incl.xsl"/><!-- last one on list has higher precedence -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="foo"/>
  </out>
</xsl:template>

</xsl:stylesheet>