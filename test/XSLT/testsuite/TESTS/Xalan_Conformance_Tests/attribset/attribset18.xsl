<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ped="http://www.ped.com"
                xmlns:bdd="http://www.bdd.com">

  <!-- FileName: attribset18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Verify adding an attribute to an element replaces any
       existing attribute of that element with the same expanded name. -->

<xsl:template match="/">
 <root><xsl:text>&#10;</xsl:text>
   <Out>
      <xsl:attribute name="attr1">Wrong</xsl:attribute>
      <xsl:attribute name="ped:attr1">Wrong</xsl:attribute>
      <xsl:attribute name="bdd:attr1">Wrong</xsl:attribute>
      <xsl:attribute name="attr2">Wrong</xsl:attribute>
	  <xsl:attribute name="bdd:attr1">Test1-OK</xsl:attribute>
      <xsl:attribute name="ped:attr1">Test2-OK</xsl:attribute>
      <xsl:attribute name="attr1">Hello</xsl:attribute>
      <xsl:attribute name="attr2">Test2</xsl:attribute>
      <xsl:attribute name="attr2">Goodbye</xsl:attribute>
   </Out>
 </root>
</xsl:template>

</xsl:stylesheet>