<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml"/>

  <!-- FileName: k -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.1 XSLT Namespace. -->
  <!-- Purpose: Imported by other tests.  -->

<xsl:template match="doc" priority="2.0">
  <out>
    <xsl:value-of select="'In Import: Testing '"/>
    <xsl:for-each select="*">
      <xsl:value-of select="."/><xsl:text> </xsl:text>		
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>