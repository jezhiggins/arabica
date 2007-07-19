<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" 
            doctype-public="-//W3C//DTD HTML 4.0 Transitional"/>

  <!-- FileName: outp36 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Processing instructions should be terminated with ">". -->

<xsl:template match="/">
 <HTML>
   <?PI1 Dothis ?>
   <?PI2 Dothat ?>
   <xsl:processing-instruction name="my-pi">href="book.css" type="text/css"</xsl:processing-instruction>
 </HTML>
</xsl:template>
 
</xsl:stylesheet>