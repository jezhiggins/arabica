<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

  <!-- FileName: copy27 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Oliver Becker -->
  <!-- Purpose: Demonstrate copying a named template from the stylesheet
    into the result. From a thread on XSL-list 7/30/2001. -->

<xsl:template name="qq">
  <node attr="8"/>
</xsl:template>
 
<xsl:template match="/">
  <results>
    <usual-result>
      <xsl:call-template name="qq"/>
    </usual-result>
    <xsl:text>&#10;</xsl:text>
    <exotic-result>
      <xsl:copy-of select="document('')/*/xsl:template[@name='qq']/node()" />
    </exotic-result>
  </results>
</xsl:template>

</xsl:stylesheet>