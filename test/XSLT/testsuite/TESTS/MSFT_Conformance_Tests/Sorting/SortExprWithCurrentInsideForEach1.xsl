<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:variable name="MyGroup">groupC</xsl:variable><!--normally this would be a param-->

<xsl:variable name="MyParts" select="document('parts.xml')/parts"/>

<xsl:template match="/large-collection">
	<xsl:apply-templates select="collection[@name = $MyGroup]" />
</xsl:template>

<xsl:template match="/large-collection/collection">
 	<xsl:for-each select="ref">
  		<xsl:sort select="$MyParts/part[@id = (current())/@refid]/@type"  order="ascending"/>
  		<xsl:sort select="$MyParts/part[@id = (current())/@refid]/@id"  order="ascending"/>
type: <xsl:value-of select="concat($MyParts/part[@id = (current())/@refid]/@type, ' name: ', $MyParts/part[@id =  (current())/@refid]/@name, ' id: ', $MyParts/part[@id = (current())/@refid]/@id)"/>
 	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
