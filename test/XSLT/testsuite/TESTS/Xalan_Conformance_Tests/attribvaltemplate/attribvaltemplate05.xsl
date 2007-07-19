<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribvaltemplate05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Use of Curly brace to set value of HTML attribute. -->

<xsl:output method="html" indent="no"/>

<xsl:template match="/">
<HTML>
  <a href="/cgi-bin/app?p_parm1={.//doc2/doc3/a/@level}"></a>
</HTML>
</xsl:template>

</xsl:stylesheet>
