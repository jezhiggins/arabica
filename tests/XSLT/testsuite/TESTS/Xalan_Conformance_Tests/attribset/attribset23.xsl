<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset23 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: XSLT processors may make use of the prefix of the QNAME specified
       in the name attribute ... however they are not required to do so and, if 
       the prefix is xmlns, they must not do so ... this will not result in a 
       namespace declaration being output. -->

<xsl:template match="/">
 <root>
  <Out>
	<xsl:attribute name="xmlns:xsl" namespace="http://whatever">http://www.w3.org/1999/XSL/Transform</xsl:attribute>
  </Out>
 </root>
</xsl:template>

</xsl:stylesheet>
