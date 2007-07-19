<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="no"
            doctype-public="-//W3C//DTD HTML 4.0 Transitional"/>

  <!-- FileName: outp59 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.3 Creating Processing Instructions -->
  <!-- Purpose: Test creation of a top-level processing-instruction before the 
                document element. -->

<xsl:template match="/">
 <xsl:processing-instruction name="my-pi">href="book.css" type="text/css"</xsl:processing-instruction>
 <HTML>
   <?PI1 Dothis ?>
   Literal output
 </HTML>
</xsl:template>
 
</xsl:stylesheet>
