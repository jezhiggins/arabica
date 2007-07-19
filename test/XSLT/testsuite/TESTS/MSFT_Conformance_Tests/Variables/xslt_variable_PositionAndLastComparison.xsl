<xsl:stylesheet version= '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  

<!-- This stylesheet is a regression test case for bug 60525. It validates that the
the last() and position() functions can be compared. -->
 
	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match="/">  
	    <xsl:for-each select="//item">
		<xsl:if test="position()=last()">
		    <xsl:value-of select="position()"/>
		    <xsl:value-of select="." />
		</xsl:if>
	    </xsl:for-each>
	</xsl:template>  
 
</xsl:stylesheet>  
