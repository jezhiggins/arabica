<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select76 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Try /{name} to match the document element. -->

<xsl:template match="/Q">
  <out>
    <xsl:value-of select="@level"/>
  </out>
</xsl:template>

</xsl:stylesheet>