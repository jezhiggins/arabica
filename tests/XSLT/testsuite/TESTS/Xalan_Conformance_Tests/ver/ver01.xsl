<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="8.5">

  <!-- FileName: Ver01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.5 Forwards-Compatible Processing  -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test the basics of the XSLT version declaration. Should not raise an error. -->

  <xsl:template match="/">
    <out>
      Choosing, based on value of version property.
      <xsl:choose>
        <xsl:when test="system-property('xsl:version') &gt;= 8.5">
          We are allowed to use the 8.5 feature.
          <xsl:exciting-new-8.5-feature/>
        </xsl:when>
        <xsl:otherwise>
          We are not allowed to use the 8.5 feature.
          <xsl:message>This stylesheet requires XSLT 8.5 or higher</xsl:message>
        </xsl:otherwise>
      </xsl:choose>
    </out>
  </xsl:template>

</xsl:stylesheet>
