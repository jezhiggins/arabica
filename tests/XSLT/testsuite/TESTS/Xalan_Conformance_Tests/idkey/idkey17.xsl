<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test key() with a node-set as second argument. -->

  <!-- "When the second argument to key is of type node-set,
       then the result is the union of the result of applying
       the key function to the string value of each of
       the nodes in the argument node-set." -->

<xsl:key name="mykey" match="div" use="title" />

<xsl:template match="doc">
 <root>
  <xsl:for-each select="key('mykey',*//title)">
    <xsl:value-of select="p"/>
  </xsl:for-each>
 </root>
</xsl:template>

</xsl:stylesheet>
