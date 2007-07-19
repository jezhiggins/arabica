<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6.2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Loads document from an included file that resides in
       a different subdirectory. -->

<xsl:include href="../impincl-test/impincl08.xsl"/>

<xsl:template match="/">
  <out>
    <xsl:call-template name="TestInclude"/>
  </out>
</xsl:template>

</xsl:stylesheet>
