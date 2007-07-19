<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:ped="http://www.ped.com">

  <!-- FileName: namespace54 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Use xsl:element with a namespace that has AVT, introduces new namespace. -->

<xsl:template match="/">
 <out>
   <xsl:element name="{docs/c}" namespace="{docs/c/@href}"/>
 </out>
</xsl:template>

</xsl:stylesheet>
