<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for xsl:key matching multiple keys on same node. -->
  <!-- "There can be multiple keys in a document with the same node, same key name,
       but different key values." -->

<xsl:key name="mykey" match="div" use="title" />

<xsl:template match="doc">
 <root>
  <xsl:value-of select="key('mykey', 'Introduction')/p"/>
  <xsl:value-of select="key('mykey', 'Stylesheet Structure')/p"/>
  <xsl:value-of select="key('mykey', 'Expressions')/p"/>
  <xsl:value-of select="key('mykey', 'Second Title in Structure')/p"/>
 </root>
</xsl:template>

</xsl:stylesheet>
