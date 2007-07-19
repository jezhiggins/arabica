<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES56 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that combination of // and descendant specifies node can be anywhere in ancestry. -->

<xsl:template match="doc">
  <out>

  <xsl:for-each select="//xx/descendant::*">
    <xsl:value-of select="name(.)"/><xsl:text> </xsl:text>
  </xsl:for-each>

  </out>
</xsl:template>

</xsl:stylesheet>