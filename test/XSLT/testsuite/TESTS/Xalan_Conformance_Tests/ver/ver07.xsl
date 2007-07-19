<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="2.0">

  <!-- FileName: Ver07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.5 Forwards-Compatible Processing  -->
  <!-- Creator: Shane Curcuru -->
  <!-- Purpose: Test the basics of the XSLT version declaration. Should not raise an error. -->

  <xsl:template match="/">
    <out>
      <xsl:text>xsl:choose when test="system-property('xsl:version') &gt;= 2.0"</xsl:text>
      <choose>
      <xsl:choose>
        <xsl:when test="system-property('xsl:version') &gt;= 2.0">
          <xsl:text>Hey! Call the 2.0 feature!</xsl:text>
          <xsl:result-document/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>Hey! 2.0 features are not supported!</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      </choose>
    </out>
  </xsl:template>

</xsl:stylesheet>
