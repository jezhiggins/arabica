<?xml version='1.0'?>
<xsl:stylesheet version="1.0" 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: variable50 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 -->
  <!-- Author: Scott Boag -->
  <!-- Purpose: Ensure that we can find descendants of the nodes
    in a node-set stored in a variable. -->

<xsl:template match="/">
  <out>
    <xsl:variable name="in" select="*/p"/>	
    <xsl:for-each select="$in//text()">
      <xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>