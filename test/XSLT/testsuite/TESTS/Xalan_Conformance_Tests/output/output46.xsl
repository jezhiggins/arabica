<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output46 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16 Output -->
  <!-- Purpose: All xsl:output elements are merged into a single element. While repeats of
    most attributes are just tested for conflicts, cdata-section-elements will contain the
    union of the specified values. Both example and test should be wrapped by CDATA, and
    the output should be XML (since cdata-section-elements only applies to XML). -->

<xsl:output cdata-section-elements="test" encoding="UTF-8" indent="no"/>
<xsl:output method="xml" cdata-section-elements="example"/>

<xsl:template match="/">
  <out>
    <example>&lt;foo></example>
    <plain>bar &amp; ban</plain>
    <test>!&gt;</test>
  </out>
</xsl:template>

</xsl:stylesheet>