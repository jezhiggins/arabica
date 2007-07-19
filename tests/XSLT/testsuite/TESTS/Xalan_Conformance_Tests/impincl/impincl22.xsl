<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6 Combining Stylesheets -->
  <!-- Creator: David Marston -->
  <!-- Purpose: With two imports, precedence goes to the last one.
    Import precedence for templates matching foo (f imports g) is
    (high) h, f, g (low) -->

<xsl:import href="f.xsl"/>
<xsl:import href="h.xsl"/>

<xsl:template match="/">
  <out>
    <xsl:apply-templates select="foo"/>
  </out>
</xsl:template>

</xsl:stylesheet>