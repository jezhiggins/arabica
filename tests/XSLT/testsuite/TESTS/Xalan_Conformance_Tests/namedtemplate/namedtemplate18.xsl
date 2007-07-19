<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namedtemplate18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 6 Named Templates -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test import precedence: main stylesheet wins over imported one. -->
  <!-- Output should be 'Template from MAIN has been called.' -->

<xsl:import href="ntimpa.xsl"/>

<xsl:template match="doc">
  <out>
    <xsl:call-template name="show"/>
  </out>
</xsl:template>

<xsl:template name="show">
  <xsl:text>Template from MAIN has been called.</xsl:text>
</xsl:template>

</xsl:stylesheet>