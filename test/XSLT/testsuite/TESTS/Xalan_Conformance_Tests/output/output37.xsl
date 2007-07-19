<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" 
    doctype-public="-//W3C//DTD HTML 4.0 Transitional"/>

  <!-- FileName: OUTP37 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: "&" should not be escaped when occuring in an attribute value
     immediately followed by a "{". See to Section B.7.1 HTML 4.0 Recommendation. -->

<xsl:template match="/">
  <HTML>
    <Body bgcolor='&amp;{{randomrbg}};'/>
  </HTML>
</xsl:template>

</xsl:stylesheet>