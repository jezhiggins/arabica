<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
<!-- Template parameters. -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->

<xsl:template match="/">
    <xsl:apply-templates select="sold_books"/>
</xsl:template>

<xsl:template name="sales_tax">
	<xsl:param name="tax">0</xsl:param>
	<xsl:value-of select="buyer_name"/> Bought <xsl:value-of select="name"/> at <xsl:value-of select="$tax"/>
	<xsl:text> percent tax</xsl:text><br/>
</xsl:template>

<xsl:template match="book">
  <xsl:call-template name="sales_tax">
    <xsl:with-param name="tax">5</xsl:with-param>
  </xsl:call-template>
</xsl:template>

<xsl:template match="milk">
  <xsl:call-template name="sales_tax">
    <xsl:with-param name="tax">3</xsl:with-param>
  </xsl:call-template>
</xsl:template>

<xsl:template match="parmesan_cheese">
  <xsl:call-template name="sales_tax" />
</xsl:template>

</xsl:stylesheet>