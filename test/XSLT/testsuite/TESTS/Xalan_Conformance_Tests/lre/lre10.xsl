<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
	xmlns:ext="http://somebody.elses.extension"
      extension-element-prefixes="ext">

  <!-- FileName: lre10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements-->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show that attributes from extension namespaces cause inclusion of the namespace node. -->
  <!-- Purpose: The created element node will also have a copy of the namespace nodes 
       that were present on the element node in the stylesheet tree with the exception 
       of any namespace node whose string-value is the XSLT namespace URI, a namespace 
       URI declared as an extension namespace, or a namespace URI designated as an 
       excluded namespace. -->

<xsl:template match="doc">
  <out ext:size="big" english="to leave"/>
</xsl:template>

</xsl:stylesheet>