<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Purpose: This test verifies correct URI resolution with relative URI's. --> 
  <!-- Case: import, import, include -->

<xsl:import href="import1/level1_import2.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="root">
 <out>
  case of import, import, include
  importing level1_import2.xsl
  <xsl:apply-templates/>
 </out>
</xsl:template>

</xsl:stylesheet>