<?xml version="1.0" ?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:import href="impattset45a.xsl" /> 
<xsl:import href="impattset45b.xsl" /> 


<!-- FileName: attribset45 -->
<!-- Document: http://www.w3.org/TR/xslt -->
<!-- DocVersion: 19991116 -->
<!-- Section: 12.1 -->
<!-- Creator: Richard Titmuss (richard@rockingfrog.com) -->
<!-- Purpose: Basic test of import precedence with attribute sets -->


<xsl:template match="/">
<out>
	<foo xsl:use-attribute-sets="bar" /> 
</out> 
</xsl:template>

</xsl:stylesheet>