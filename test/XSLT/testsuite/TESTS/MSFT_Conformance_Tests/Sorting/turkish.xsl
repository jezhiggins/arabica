<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>

<!-- Created by PJoshi -->

<xsl:output method="xml" indent="yes"/>

<xsl:template match="data">
    <RESULT>
	  <xsl:for-each select="a" >
		<xsl:sort lang="tr" select="." order="ascending" case-order="upper-first"/>
		<asc_upperfirst>
			<xsl:value-of select='.' />
		</asc_upperfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="tr" select="." order="ascending" case-order="lower-first"/>
		<asc_lowerfirst>
			<xsl:value-of select='.' />
		</asc_lowerfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="tr" select="." order="descending" case-order="upper-first"/>
		<desc_upperfirst>
			<xsl:value-of select='.' />
		</desc_upperfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="tr" select="." order="descending" case-order="lower-first"/>
		<desc_lowerfirst>
			<xsl:value-of select='.' />
		</desc_lowerfirst>
	  </xsl:for-each>
    </RESULT>

    <RESULT>
	  <xsl:for-each select="a" >
		<xsl:sort lang="en" select="." order="ascending" case-order="upper-first"/>
		<asc_upperfirst>
			<xsl:value-of select='.' />
		</asc_upperfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="en" select="." order="ascending" case-order="lower-first"/>
		<asc_lowerfirst>
			<xsl:value-of select='.' />
		</asc_lowerfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="en" select="." order="descending" case-order="upper-first"/>
		<desc_upperfirst>
			<xsl:value-of select='.' />
		</desc_upperfirst>
	  </xsl:for-each>

	  <xsl:for-each select="a" >
		<xsl:sort lang="en" select="." order="descending" case-order="lower-first"/>
		<desc_lowerfirst>
			<xsl:value-of select='.' />
		</desc_lowerfirst>
	  </xsl:for-each>
    </RESULT>
</xsl:template>
	
</xsl:stylesheet>
