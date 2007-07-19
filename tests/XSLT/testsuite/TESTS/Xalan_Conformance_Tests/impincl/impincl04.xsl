<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6.1 -->
  <!-- Purpose: Verifies; "A relative URI is resolved relative to the
       base URI of the xsl:include element". The included document loads
       from an included file that resides in a different subdirectory. -->

<xsl:include href="../impincl-test/impincl04.xsl"/>

<xsl:template match="/">
  <out>
    <xsl:call-template name="TestInclude"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
