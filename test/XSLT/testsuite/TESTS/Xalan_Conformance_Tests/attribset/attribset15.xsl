<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:ped="http://ped.test.com">

  <!-- FileName: attribset15 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Discretionary: name="attribute-name-not-QName" choice="ignore" -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: The name attribute is interpreted as an attribute value template.
       It is an error if the value of the AVT is not a QNAME or the string "xmlns".
       (Last two xsl:attributes test this)  -->

<xsl:template match="/">
  <out xmlns:this="http://www.this.com">
  	<xsl:attribute name="{doc/First/@at}">First</xsl:attribute>
  	<xsl:attribute name="{doc/Second/@at}">Second</xsl:attribute>
  	<xsl:attribute name="{doc/Third/@at}">Third</xsl:attribute>
  	<xsl:attribute name="xmlns">xmlns</xsl:attribute>
  </out>
</xsl:template>

</xsl:stylesheet>