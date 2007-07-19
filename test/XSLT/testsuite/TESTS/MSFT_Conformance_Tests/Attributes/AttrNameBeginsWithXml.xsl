<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- This is a regression case for bug 81785 -->

<!-- XSLT: Xslt processor should be able to output attribute whose name begins with 'xml' -->

<xsl:output method="xml" encoding="utf-8" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<out>
		<xsl:attribute name="xmlA:attr" namespace="my"/>
	</out>
</xsl:template>

</xsl:stylesheet>