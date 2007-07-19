<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namedtemplate17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 6 Named Templates -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test import precedence: both ntimpa and ntimpb have "show" template, b wins. -->
  <!-- Output should be 'Template from ntimpb has been called.' -->

<xsl:import href="ntimpa.xsl"/>
<xsl:import href="ntimpb.xsl"/>

<xsl:template match="doc">
  <out>
    <xsl:call-template name="show"/>
  </out>
</xsl:template>

</xsl:stylesheet>