<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output38 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Meta should be added immediately after after the start-tag
     of the HEAD element specifying the character encoding actually used. -->

<xsl:output method="html" encoding="ISO-8859-1"
  doctype-public="-//W3C//DTD HTML 4.0 Transitional"/>

<xsl:template match="/">
  <HTML>
    <HEAD>
      <Body>Hi</Body>
    </HEAD>
  </HTML>
</xsl:template>

</xsl:stylesheet>