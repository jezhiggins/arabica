
<html xsl:version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:for-each select="//magazine/title">
	<span style="color:green">
	<xsl:value-of select="name()"/> : <xsl:value-of select="."/> </span><br/>
<xsl:apply-templates/>
</xsl:for-each>
<xsl:apply-templates/>
</html>
