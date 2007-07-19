<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template name="temp1">

               <xsl:for-each select="key('prices', '1')[@attr='ddd']">
			<xsl:value-of select="."/>
               </xsl:for-each>
  
    </xsl:template>

    <xsl:key name="prices" match="price" use="@foo"/>

</xsl:stylesheet>
