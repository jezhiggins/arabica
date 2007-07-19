<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" doctype-public="-//W3C//DTD HTML 4.0 Transitional" indent="no"/>

  <!-- FileName: outp48 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose:  ... html output method should output a DTD immediately
       before the first element. -->

<xsl:template match="/">
 <root>
 Please <b>BOLD THIS</b> now.
 </root>
</xsl:template>

</xsl:stylesheet>
