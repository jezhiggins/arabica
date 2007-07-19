<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:ped="http://ped.test.com">

  <!-- FileName: attribset14 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Use xsl:element with attribute having a namespace. The expanded-name of 
       the attribute to be created is specified by a required name attribute and an 
       optional namespace attribute -->

<xsl:template match="doc">
  <xsl:element name="ped:Out">
    <xsl:attribute name="test1">xsl:element Attribute</xsl:attribute>
    <xsl:attribute name="test2" namespace="http://ped.test.com">xsl:element Attribute</xsl:attribute>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>