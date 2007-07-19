<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP56 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Test creating a comment from a variable. -->

<xsl:variable name="commentor">foo</xsl:variable>

<xsl:template match="/">
  <Out>
    <xsl:comment><xsl:value-of select="$commentor"/></xsl:comment>
  </Out>
</xsl:template>

</xsl:stylesheet>