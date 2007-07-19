<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: SORT33 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Try to set order from a variable. -->

<xsl:template match="doc">
  <xsl:variable name="ord" select="'descending'"/>
  <out>
    Descending order....
    <xsl:for-each select="t">
      <xsl:sort data-type="number" order="{$ord}"/>
      <xsl:value-of select="."/><xsl:text>|</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
