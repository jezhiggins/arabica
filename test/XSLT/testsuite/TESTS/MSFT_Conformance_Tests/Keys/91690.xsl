<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes"/>


<xsl:key name="term" match="p" use=".//term" />

<xsl:template match="/">
    <HTML>
      <BODY>
          <UL>
          <xsl:for-each select="key('term', 'middle tier')" >
               <LI><xsl:value-of select="substring(.,1,34)"/></LI>
          </xsl:for-each>
          </UL>
      </BODY>
    </HTML>
</xsl:template>

</xsl:stylesheet>