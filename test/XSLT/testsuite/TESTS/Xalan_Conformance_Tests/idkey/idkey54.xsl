<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey54 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for xsl:key and key() with a leaing underscore in the name. -->

<xsl:key name="_my_key" match="div" use="title"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="key('_my_key', 'Introduction')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('_my_key', 'Stylesheet Structure')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('_my_key', 'Expressions')/p"/>
  </out>
</xsl:template>

</xsl:stylesheet>
