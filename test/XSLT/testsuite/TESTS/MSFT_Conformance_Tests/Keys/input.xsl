<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:key name="Entity_key" match="Firm_Subsidiary_Relationship/Parent" use="Entity_id"/>

 <xsl:template match="InputXML">
    <OutputXML>
  
    <xsl:apply-templates select="Firm_Subsidiary_Relationship"/>
   
    </OutputXML>
</xsl:template>

<xsl:template match="Firm_Subsidiary_Relationship">
  <xsl:for-each select="Parent[count(.| key('Entity_key', Entity_id)[1])=1]">
            <Entity>
              <Entity_id>
                  <xsl:value-of select="."/>
              </Entity_id>
              <Subsidiaries>
                <xsl:for-each select="key('Entity_key', Entity_id)">
                  <xsl:for-each select="parent::node()/Subsidiary/Entity_id">
                       <xsl:copy-of select="."/>
                  </xsl:for-each>
                </xsl:for-each>
              </Subsidiaries>
            </Entity>
  </xsl:for-each>
 </xsl:template>
</xsl:stylesheet>

  