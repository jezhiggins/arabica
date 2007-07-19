<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:text disable-output-escaping="yes">
	&lt;foo&gt;
	&quot; &amp;amp; Hello &apos;
	&lt;/foo&gt;
	</xsl:text>
    </xsl:template>
</xsl:stylesheet>
