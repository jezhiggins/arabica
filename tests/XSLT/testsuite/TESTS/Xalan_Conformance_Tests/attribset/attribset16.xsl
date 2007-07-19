<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:ped="http://ped.test.com">

  <!-- FileName: attribset16 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: The namespace attribute is interpreted as an attribute value template. -->

<xsl:template match="/">
 <root><xsl:text>&#10;</xsl:text>
  <Out>
	<xsl:attribute name="{docs/a}" namespace="{docs/a/@href}">Hello</xsl:attribute>
	<xsl:attribute name="{docs/b}" namespace="{docs/b/@href}">Whatsup</xsl:attribute>
	<xsl:attribute name="Attr2" namespace="http://ped.test.com">Goodbye</xsl:attribute>
  </Out>
 </root>
</xsl:template>

</xsl:stylesheet>