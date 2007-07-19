<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

<xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

	<xsl:template match="/">
	    <xsl:apply-templates select="//last-name" mode="formatting-tests"/>
	</xsl:template>

	<xsl:template match="last-name" mode="formatting-tests">

		<xsl:number level="multiple" count="last-name | publication | author | book" format="A.1"/><xsl:text>, </xsl:text>

		<xsl:value-of select="concat(../first-name, ' ', .)"/>

	</xsl:template>

</xsl:stylesheet>
