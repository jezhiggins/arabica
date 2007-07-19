<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace20 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Simple case verifies use of xml:space to preserve whitespace,
  	   here a space and a tab. -->

<xsl:template match="/">
 <root><xsl:text>&#10;</xsl:text>
   <out>    </out><xsl:text>&#10;</xsl:text>
   <out xml:space="default"> 	</out><xsl:text>&#10;</xsl:text>
   <out xml:space="preserve"> 	</out><xsl:text>&#10;</xsl:text>
   <out xml:space="default"> 	</out><xsl:text>&#10;</xsl:text>
 </root>
</xsl:template>

</xsl:stylesheet>