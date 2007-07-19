<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:baz="http://baz.com" xmlns="http://baz.com"
  exclude-result-prefixes="baz">

  <!-- FileName: OUTPUT101 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show that LRE in default namespace can match namespaced element in cdata-section-elements list. -->

<xsl:output method="xml" cdata-section-elements="baz:out" encoding="UTF-8"/>

<xsl:template match="/">
  <out>should be wrapped</out>
</xsl:template>
 
</xsl:stylesheet>