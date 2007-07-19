<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace19 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Stylesheet is whitespace stripped before processing. -->

<xsl:template match="/">
<out>
<xsl:for-each select="doc/alpha">
    <xsl:value-of select="@key"/>|<xsl:text/> </xsl:for-each>



</out>
</xsl:template>

</xsl:stylesheet>