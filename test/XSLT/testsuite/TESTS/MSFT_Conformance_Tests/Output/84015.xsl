<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 <!-- escapechars in http://webxtest/testcases/xslt05001.xml -->

<xsl:output method="text"/>  



  <xsl:template match="/">
          <xsl:for-each select="EscapeChars">
				<xsl:apply-templates/>
          </xsl:for-each>
  </xsl:template>   

  <xsl:template match="EscapeChars/Char">
    <xsl:value-of select="Char"/>
  </xsl:template>


</xsl:stylesheet>  
