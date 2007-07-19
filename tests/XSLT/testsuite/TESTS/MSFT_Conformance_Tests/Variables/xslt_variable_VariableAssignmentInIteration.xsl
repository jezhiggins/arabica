<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


    <!-- Generate standard template for managed test spec -->
    <xsl:template match="/">
	<testmodule>
    	    <xsl:apply-templates select="variations/variation"/>
	</testmodule>
    </xsl:template>

    <!-- Add case: Add the new variation -->
    <xsl:template match="variation">
	<variation>
	    <test type="xslt">
		<xsl:variable name="ExpResult" select="@case_id"/>
		<Result>
		    <xsl:value-of select="@case_id"/>
		</Result>
		<WriterResult>
		    <xsl:value-of select="$ExpResult"/>
		</WriterResult>
	    </test>
	</variation>
    </xsl:template>

</xsl:stylesheet>