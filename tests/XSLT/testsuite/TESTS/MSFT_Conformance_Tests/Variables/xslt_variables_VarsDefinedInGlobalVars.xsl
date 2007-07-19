<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a regression test case for bug 66748. -->

	<xsl:output omit-xml-declaration="yes" />

	<xsl:variable name="x1">
		<xsl:variable name='y1' select="'var(y1)'"/>	
		<foo attr="{$y1}" />
	</xsl:variable>

	<xsl:variable name="x2">
		<xsl:variable name='y1' select="'var(y1)'"/>	
		<foo attr="{$y1}" />
	</xsl:variable>

	<xsl:variable name="x3">
		<xsl:variable name='y2' select="'var(y2)'"/>	
		<bar><xsl:value-of select="$y2"/></bar>
	</xsl:variable>

	<xsl:template match="/" xml:space='preserve'>
	   <xsl:copy-of select='$x1'/>
	   <xsl:copy-of select='$x2'/>
	   <xsl:copy-of select='$x3'/>
	</xsl:template>

</xsl:stylesheet>