<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output cdata-section-elements="example" encoding="US-ASCII"/>

  <!-- FileName: OUTP28 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method-->
  <!-- Purpose: Result tree here defaults to XML
       Test for cdata-section-elements with nonrepresentable character. -->

<xsl:template match="doc">
  <out>
    <example>this character: &#10052; is a snowflake.</example>
  </out>
</xsl:template>

</xsl:stylesheet>
