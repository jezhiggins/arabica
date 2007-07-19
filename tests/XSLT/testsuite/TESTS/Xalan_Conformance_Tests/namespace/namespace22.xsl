<?xml version="1.0"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns="http://spacename.com">

  <!-- FileName: namespace22-->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1 Creating Elements (Namespace Node Inheritance) -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Show how namespaces are inherited down to succeeding elements. -->

<xsl:template match = "doc">
  <out>
    <xsl:text>&#010;</xsl:text>
    <middle/>
    <xsl:element name="element2"/>
  </out>
</xsl:template>

</xsl:stylesheet>