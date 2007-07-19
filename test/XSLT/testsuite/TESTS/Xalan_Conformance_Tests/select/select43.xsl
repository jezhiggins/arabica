<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select43 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: NodeSet union using the ancestor axis -->
  <!-- Creator: Carmelo Montanez --><!-- Expression003 in NIST suite -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//child1">
      <xsl:apply-templates select="ancestor::sub1|ancestor::sub2"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:value-of select="@pos"/>
</xsl:template>

</xsl:stylesheet>

