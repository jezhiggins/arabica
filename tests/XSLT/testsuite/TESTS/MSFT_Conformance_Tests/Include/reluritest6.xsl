<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Purpose: This test verifies correct URI resolution with relative URI's. --> 
  <!-- Case: import, include with a rel path -->

<xsl:import href="import1/level1_import3.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="root">
 <out>
  case of import, include with a rel path
  importing level1_import3.xsl
  <xsl:apply-templates/>
 </out>
</xsl:template>

</xsl:stylesheet>