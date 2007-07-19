<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:baz="http://baz.com" xmlns:extra="http://baz.com"
  exclude-result-prefixes="extra">

  <!-- FileName: OUTPUT103 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show that namespaced LRE can match differently-prefixed element in cdata-section-elements. -->

<xsl:output method="xml" cdata-section-elements="extra:out" encoding="UTF-8"/>

<xsl:template match="/">
  <baz:out>should be wrapped</baz:out>
</xsl:template>
 
</xsl:stylesheet>