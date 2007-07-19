<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace116 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Try to put un-namespaced attribute on namespaced element. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="/">
  <out xmlns:foo="http://foo.com">
    <foo:pq>
      <xsl:attribute name="Attr1" namespace="">true</xsl:attribute>
    </foo:pq>
  </out>
</xsl:template>

</xsl:stylesheet>