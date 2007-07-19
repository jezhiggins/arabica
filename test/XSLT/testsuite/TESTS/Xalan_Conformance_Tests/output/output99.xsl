<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:baz="http://baz.com">

  <!-- FileName: OUTPUT99 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Bertoni -->
  <!-- Purpose: Show that namespaced LRE does not match unprefixed element in cdata-section-elements list. -->

<xsl:output method="xml" cdata-section-elements="out" encoding="UTF-8"/>

<xsl:template match="/">
  <baz:out>should NOT be wrapped</baz:out>
</xsl:template>
 
</xsl:stylesheet>