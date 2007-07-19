<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output encoding="Big-Deal"/>

  <!-- FileName: output77 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Test of ficticous encoding. This is generating an Illegal 
       argument exception, with other known encodings such as "ISO-8859-11" 
       too -->

<xsl:template match="/">
  <out>
    <test>Testing</test>
  </out>
</xsl:template>

</xsl:stylesheet>
