<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  
<xsl:template match="/">

<xsl:text disable-output-escaping="yes">&lt;foo&gt;""&amp;amp;"&lt;bar&gt;""&lt;/bar&gt;""&lt;/foo&gt;</xsl:text>	

</xsl:template>

</xsl:stylesheet>
