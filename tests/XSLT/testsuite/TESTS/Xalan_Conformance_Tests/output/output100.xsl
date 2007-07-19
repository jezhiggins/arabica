<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:baz="http://baz.com"
  exclude-result-prefixes="baz">

  <!-- FileName: OUTPUT100 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show that non-namespaced LRE does not match namespaced element in cdata-section-elements list. -->

<xsl:output method="xml" cdata-section-elements="baz:out" encoding="UTF-8"/>

<xsl:template match="/">
  <out>should NOT be wrapped</out>
</xsl:template>
 
</xsl:stylesheet>