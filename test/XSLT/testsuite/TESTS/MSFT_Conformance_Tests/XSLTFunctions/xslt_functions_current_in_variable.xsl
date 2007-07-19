<?xml version='1.0' encoding='utf-8' ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<root>
				<!--I'm not sure how to do a negative ansccestor test so I left this blank instead-->
				<xsl:for-each select="descendant::*">
						<xsl:variable name="vLookupList" select="/root/ReportText/Node[@Name = name(current())]" />
						<xsl:value-of select="$vLookupList"/>
				</xsl:for-each>
		</root>		
	</xsl:template>
</xsl:stylesheet>
