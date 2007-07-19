<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey34 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test descendants of node-set from key(). -->

<xsl:key name="mykey" match="div" use="title" />

<xsl:template match="doc">
  <out>
    <xsl:for-each select="key('mykey', 'Introduction')//p">
      <xsl:value-of select="."/><xsl:text>
</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
