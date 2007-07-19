<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP57 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Test use of xsl:if and xsl:text inside xsl:comment. -->

<xsl:template match="/">
  <Out>
    <xsl:comment>
      <xsl:if test="true()">
        <xsl:text>Comment content</xsl:text>
      </xsl:if>
    </xsl:comment>
  </Out>
</xsl:template>

</xsl:stylesheet>