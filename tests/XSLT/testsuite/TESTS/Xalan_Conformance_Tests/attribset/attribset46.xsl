<?xml version="1.0" ?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:import href="impattset46a.xsl" /> 
<xsl:import href="impattset46b.xsl" /> 


<!-- FileName: attribset46 -->
<!-- Document: http://www.w3.org/TR/xslt -->
<!-- DocVersion: 19991116 -->
<!-- Section: 12.1 -->
<!-- Creator: Paul Dick  -->
<!-- Purpose: Basic test of import precedence based on Richard Titmuss's test
     with attribute sets. Here the imported attribute sets have additional non-
     conflicting attributes as well.  -->


<xsl:template match="/">
<out>
	<foo xsl:use-attribute-sets="bar" /> 
</out>
</xsl:template>

</xsl:stylesheet>