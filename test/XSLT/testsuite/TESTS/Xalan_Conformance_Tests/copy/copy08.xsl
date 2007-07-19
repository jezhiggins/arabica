<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 Using values of variables and parameters with xsl:copy-of. -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of passing HTML to a named template. -->

<xsl:template match="/">
  <out>
    <xsl:call-template name="format">
      <xsl:with-param name="nodetext">Please <b>BOLD THIS</b> now.</xsl:with-param>
    </xsl:call-template>
  </out>		 
</xsl:template>

<xsl:template name="format">
  <xsl:param name="nodetext">bla bla bla</xsl:param>
  <xsl:copy-of select="$nodetext"/>
</xsl:template>

</xsl:stylesheet>
