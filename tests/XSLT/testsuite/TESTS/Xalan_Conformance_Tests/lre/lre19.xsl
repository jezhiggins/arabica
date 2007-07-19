<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
				xmlns:_ped="http://www.ped.com">
  <!-- FileName: lre19 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test use of leading underscore in names. -->

<xsl:template match="/">
 <root>
   <xsl:text>&#10;</xsl:text>
   <xsl:element name="_an_elem" namespace="{docs/a/@href}"/>
   <xsl:text>&#10;</xsl:text>
   <xsl:element name="_ped:_an_elem"/>
 </root>
</xsl:template>

</xsl:stylesheet>
