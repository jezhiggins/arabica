<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9 -->
  <!-- Creator: Carmelo Montanez --><!-- DataManipulation001 in NIST suite -->
  <!-- Purpose: Test xsl:if inside xsl:when. -->

<xsl:template match="doc">
  <out>
    <xsl:choose>
      <xsl:when test = "2 &gt; 1">
        <xsl:if test = "9 mod 3 = 0">
          <xsl:text>Test executed successfully.</xsl:text>
        </xsl:if>
      </xsl:when>
    </xsl:choose>
  </out>
</xsl:template>

</xsl:stylesheet>
