<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: sort04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Purpose: Test for xsl:sort and value-of the same element in the same loop. -->

<xsl:template match="w3cgroup">
  <out>
    <xsl:for-each select="member">
      <xsl:sort select="affiliation"/>
      <xsl:value-of select="affiliation"/><xsl:text> </xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
