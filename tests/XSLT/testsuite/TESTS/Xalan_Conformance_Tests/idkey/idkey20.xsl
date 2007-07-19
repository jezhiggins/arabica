<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey20 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 1999116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for xsl:key being imported. -->

<xsl:import href="impidky20.xsl"/>

<xsl:template match="doc">
 <root>
    <xsl:value-of select="key('mykey', 'Introduction')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('mykey', 'Stylesheet Structure')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('mykey', 'Expressions')/p"/>
 </root>
</xsl:template>

</xsl:stylesheet>
