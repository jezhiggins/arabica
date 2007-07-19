<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for "when" testing on nonexsisent attribute node. -->
  <!-- No errors or output expected. -->

<xsl:template match="/doc">
  <out>
    <xsl:for-each select="critter">
      <xsl:choose>
        <xsl:when test="@type='horse'">&#xa;Horse: </xsl:when>
        <xsl:when test="@type='cow'">&#xa;Cow: </xsl:when>
      </xsl:choose>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
