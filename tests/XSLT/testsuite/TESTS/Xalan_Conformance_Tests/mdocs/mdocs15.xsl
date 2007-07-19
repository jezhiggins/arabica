<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: mdocs15 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test / as second argument to document().
      Two arguments: string variable, node-set. -->

<xsl:variable name="typefile" select="'mdocs15a.xml'" />

<xsl:template match="defaultcontent">
  <out>
    <xsl:copy-of select="document($typefile,/)"/>
  </out>
</xsl:template>

</xsl:stylesheet>