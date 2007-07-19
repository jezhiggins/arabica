<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
				xmlns:ped="http://www.test.com">

  <!-- FileName: lre01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Basic demonstration that namespace node is added when namespaced attribute is instantiated. -->
  <!-- Elaboration: In a template, an element in the stylesheet that does not belong to 
  the XSLT namespace and that is not an extension element is instantiated to create 
  an element node with the same expanded-name.... The created element node will 
  have the attribute nodes that were present on the element node in the stylesheet 
  tree, other than attributes with names in the XSLT namespace. -->

<xsl:template match="doc">
  <out english="to leave" ped:attr="test"/>
</xsl:template>

</xsl:stylesheet>
