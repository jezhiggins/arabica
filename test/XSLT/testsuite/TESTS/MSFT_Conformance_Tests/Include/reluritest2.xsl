<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Purpose: This test verifies correct URI resolution with relative URI's. --> 
  <!-- Case: include, include, import -->

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:include href="include1/level1_include2.xsl"/>

<xsl:template match="root">
 <out>
  case of include, include, import
  including level1_include2.xsl
  <xsl:apply-templates/>
 </out>
</xsl:template>

</xsl:stylesheet>