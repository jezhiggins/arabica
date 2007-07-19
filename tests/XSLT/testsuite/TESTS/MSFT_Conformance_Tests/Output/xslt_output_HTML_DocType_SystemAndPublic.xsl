<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" doctype-system="-//W3C//DTD HTML 4.0//EN//System" doctype-public="-//W3C//DTD HTML 4.0//EN//Public"/>

  <!-- Purpose: Test for Bug #70807. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="doc">
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>