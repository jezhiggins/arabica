<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Purpose: xsl:text node should not contribute any text nodes 
       to the result tree. -->

<xsl:template match="/">
<out><xsl:text>&#010;</xsl:text>
<xsl:for-each select="doc/alpha">
   <xsl:value-of select="@key"/>|<xsl:text/>
</xsl:for-each>
</out>

</xsl:template>

</xsl:stylesheet>