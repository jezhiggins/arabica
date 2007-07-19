<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="17.1">

  <!-- FileName: Ver05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.5 Forwards-Compatible Processing  -->
  <!-- Creator: Shane Curcuru -->
  <!-- Purpose: Test the basics of the XSLT version declaration. Should not raise an error. -->
  <!-- Note that this test obviously needs updating as soon as we support XSLT 17.1! -->

  <xsl:template match="/">
    <out>
      <xsl:text>xsl:choose when test="system-property('xsl:version') &gt;= 17.1"</xsl:text>
      <choose>
      <xsl:choose>
        <xsl:when test="system-property('xsl:version') &gt;= 17.1">
          <xsl:text>Hey! Call the 17.1 feature!</xsl:text>
          <xsl:exciting-new-17.1-feature/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>Hey! 17.1 features are not supported!</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      </choose>
    </out>
  </xsl:template>

</xsl:stylesheet>
