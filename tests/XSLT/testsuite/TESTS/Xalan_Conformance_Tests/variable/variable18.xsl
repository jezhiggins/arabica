<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.6 Passing Parameters to Templates.  -->
  <!-- Purpose: Test param being set to default in a named template. -->
  <!-- Author: David Marston -->

<xsl:template match="/">
  <out>
    <xsl:call-template name="myTmpl">
      <!-- If we had a with-param here, we could change the value of "bar". -->
    </xsl:call-template>
  </out>
</xsl:template>

<xsl:template name="myTmpl">
  <xsl:param name="bar">defaultVal</xsl:param>
    <foo>
      <xsl:value-of select="$bar"/>
    </foo>
</xsl:template>

</xsl:stylesheet>