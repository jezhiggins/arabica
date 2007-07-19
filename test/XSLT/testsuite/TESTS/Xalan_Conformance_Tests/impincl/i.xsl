<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="html"/>

<xsl:template match="one-tag">
 From Imported stylesheet: <xsl:value-of select="self::node()"/>
</xsl:template>

</xsl:stylesheet>