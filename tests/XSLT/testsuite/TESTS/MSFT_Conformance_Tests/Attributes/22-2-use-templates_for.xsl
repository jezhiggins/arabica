<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
BEFORE<xsl:apply-templates />AFTER
</xsl:template>

<xsl:template match="Plant-Sheet">Root of the document</xsl:template>
<xsl:template match="a">should never see this</xsl:template>
<xsl:template match="/Plant-Sheet/Section">Section was here</xsl:template>

</xsl:stylesheet>
