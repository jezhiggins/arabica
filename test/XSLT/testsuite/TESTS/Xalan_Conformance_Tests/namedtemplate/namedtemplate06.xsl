<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namedtemplate06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 6 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Call named template that has priority and mode. -->

  <!-- "The match, mode, and priority attributes on an xsl:template element do not affect
     whether the template is invoked by an xsl:call-template element." -->

<xsl:template match="doc">
  <out>
    <xsl:call-template name="ntmp1">
      <xsl:with-param name="pvar1" select="a"/>
    </xsl:call-template>
  </out>
</xsl:template>

<xsl:template name="ntmp1" match="no_such_element" mode="other" priority="-500">
  <xsl:param name="pvar1">Default text in pvar1</xsl:param>
  <xsl:value-of select="$pvar1"/><xsl:text> in ntmp1</xsl:text>
</xsl:template>

</xsl:stylesheet>
