<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href="84612a.xsl"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="book">
<xsl:value-of select="title"/>;
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>