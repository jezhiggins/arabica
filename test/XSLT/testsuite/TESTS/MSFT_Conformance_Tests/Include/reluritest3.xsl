<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Purpose: This test verifies correct URI resolution with relative URI's. --> 
  <!-- Case: import, include -->

<xsl:import href="import1/level1_import1.xsl"/>

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="root">
 <out>
  case of import, include, importing level1_import1.xsl
  <xsl:apply-templates/>
 </out>
</xsl:template>

</xsl:stylesheet>