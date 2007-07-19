<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: reluri01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.2 Base URI (Stylesheet import/Inclusion) -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: This test verifies correct URI resolution with relative URI's. --> 
  <!-- Case: import, import, import import-->

<xsl:import href="level1/level1_import1.xsl"/>

<xsl:template match="root-tag">
 <out>
Case of: import, import, import import
  importing level1_import1.xsl
  <xsl:apply-templates/>
 </out>
</xsl:template>

</xsl:stylesheet>