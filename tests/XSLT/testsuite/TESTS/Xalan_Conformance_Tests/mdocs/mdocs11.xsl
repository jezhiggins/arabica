<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MDocs11 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check that position() counts nodes in external document. -->

<xsl:template match="defaultcontent">
  <out>
    <xsl:apply-templates select="document('../impincl-test/mdocs11a.xml')//body"/>
  </out>
</xsl:template>

<xsl:template match="body">
  <xsl:text>Width of body </xsl:text>
  <xsl:value-of select="position()"/>
  <xsl:text> is </xsl:text>
  <xsl:value-of select="@width"/>
  <xsl:text>
</xsl:text>
</xsl:template>

</xsl:stylesheet>