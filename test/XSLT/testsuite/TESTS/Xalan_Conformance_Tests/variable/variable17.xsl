<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 -->
  <!-- Purpose: Show that there is always a current node -->
  <!-- Author: David Marston -->

<xsl:param name="children" select="count(*)"/>

<xsl:template match="docs">
  <out>
    <xsl:text>$children contains </xsl:text>
    <xsl:value-of select="$children"/>
  </out>
</xsl:template>

</xsl:stylesheet>
