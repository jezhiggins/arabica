<?xml version="1.0" encoding="ISO-8859-1"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="html" indent="no"/>

  <!-- FileName: outp70 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 1 Introduction -->
  <!-- Purpose: Quotes and apostrophes can be used inside themselves, without
     terminating the string, if entered as entities. -->

<xsl:template match="/">
  <HTML>
    Inside double quotes:
    1. "&quot;"  <A href="&quot;"/>
    2. "&apos;"  <A href="&apos;"/>
    Inside single quotes:
    3. '&quot;'  <A href='&quot;'/>
    4. '&apos;'  <A href='&apos;'/>
    NOTE: hrefs always have the double quotes.
  </HTML>
</xsl:template>

</xsl:stylesheet>
