<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:ped="http://ped.test.com">

  <!-- FileName: attribset13 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Creating attribute for Literal Result Element. The expanded-name of 
       the attribute to be created is specified by a required name attribute and an 
       optional namespace attribute -->

<xsl:template match="doc">
  <out>
	<xsl:attribute name="test1">LRE Attribute</xsl:attribute>
	<xsl:attribute name="test2" namespace="http://ped.test.com">LRE Attribute</xsl:attribute>
  </out>
</xsl:template>

</xsl:stylesheet>