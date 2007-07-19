<xsl:stylesheet version="1.0"
                      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                      xmlns:xsla="http://www.xsla.com"
	              xmlns:xslb="http://www.xslb.com" 
	              xmlns:xslc="http://www.xslc.com"
exclude-result-prefixes="xslb	xslc">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="/">
<xsla:variable name="foo">
	bar
</xsla:variable>

<xsla:element name="x">
	y
</xsla:element>

</xsl:template>

<xsl:namespace-alias stylesheet-prefix="xsla" result-prefix="xsl"/>

</xsl:stylesheet>