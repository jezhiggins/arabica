<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml"
    doctype-system="wml_11.xml"
    doctype-public="-//WAPFORUM//DTD WML1.1//EN"/>

<!-- The orginal doctype-system attrib was as below:
    	doctype-system="http://www.wapforum.org/DTD/wml_1.1.xml"
	 but it has been localized to facilatate testing. -->

  <!-- FileName: OUTP64 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Purpose: Generate output tagged for WML -->

<xsl:template match="/">
  <wml>
    <xsl:apply-templates/>
  </wml>
</xsl:template>

</xsl:stylesheet>
