<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable42 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 -->
  <!-- Purpose: Use copy to set a variable to an RTF.
       REMINDER: we won't get the whole sub-tree, just the 'doc' element node. -->
  <!-- Author: David Marston -->

<xsl:template match="doc">
  <xsl:variable name="z">
    <xsl:copy>
      <xsl:attribute name="status">replacement</xsl:attribute>
    </xsl:copy>
  </xsl:variable>
  <out>
    <xsl:text>$z contains </xsl:text>
    <xsl:copy-of select="$z"/>
  </out>
</xsl:template>

</xsl:stylesheet>
