<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" > <!-- why is the method property overidden by the included or imported stylesheet? -->
    <xsl:import href="91100a.xsl" xsl:use-attribute-sets="foo" />
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="bar" xsl:use-attribute-sets="foo">
<!-- bug
	<xsl:attribute name="foo" use-attribute-sets="foo">foo</xsl:attribute>
-->
    </xsl:attribute-set>

    <xsl:template match="bookstore" xsl:use-attribute-sets="foo">
	<xsl:text xsl:use-attribute-sets="foo" >text</xsl:text>
<!-- bug#50251  case 91099.xsl
	<xsl:comment xsl:use-attribute-set="foo" use-attribute-sets="foo">text</xsl:comment>
-->
	<xsl:for-each select="book" xsl:use-attribute-sets="foo">
		<xsl:copy xsl:use-attribute-sets="foo"/>
		<xsl:value-of xsl:use-attribute-sets="foo" select="bar"/>
	</xsl:for-each>
	<xsl:apply-templates xsl:use-attribute-sets="foo" select="bar"/>
<!-- ask ANDY??? why is no error? there is no imported xsl
	<xsl:apply-imports /> 
-->
	<xsl:call-template name="foo" xsl:use-attribute-sets="foo" > 
        <xsl:with-param name="y" xsl:use-attribute-sets="foo" >x</xsl:with-param>
	</xsl:call-template>
	<xsl:copy-of  xsl:use-attribute-sets="foo" select="not-exist"/>
	<xsl:if test="'a'='a'" xsl:use-attribute-sets="foo" > IFifIF </xsl:if>
	<xsl:number xsl:use-attribute-sets="foo" value="123" level="single" grouping-size="2"/>

      <xsl:choose  xsl:use-attribute-sets="foo">
        <xsl:when test='1=2' xsl:use-attribute-sets="foo" >
          <xsl:number format="i"/>
        </xsl:when>
        <xsl:otherwise  xsl:use-attribute-sets="foo">
          <xsl:number xsl:use-attribute-sets="foo" format="9" value="9"/>
        </xsl:otherwise>
      </xsl:choose>

	<xsl:value-of select="@*"/>
	<xsl:value-of select="'VALUE-OF'"/>
      
    </xsl:template>

    <xsl:template name="foo" match="notExist"/>
<!-- ask Andy??? is this supported?
    <xsl:decimal-format name="a" percent="abc" />
    <xsl:fallback use-attribute-sets="foo"/>
    <xsl:message terminate="yes"/>
    <xsl:sort select="book" use-attribute-sets="foo" xsl:use-attribute-sets="foo" value="123" level="single" grouping-size="2"/>
-->
<!-- ask Andy??? Why is this over take the output of the template??
    <xsl:import href="http://webxtest/testcases/simple.xml"/>
    <xsl:include href="http://webxtest/testcases/simple.xml"/>
    <xsl:key name="key" match="/" use="*"/>
    <xsl:namespace-alias stylesheet-precid="#decault" result-prefix="#default"/>
    <xsl:transform is="a1"/>
-->
    <xsl:include href="91100a.xsl" xsl:use-attribute-sets="foo" />
    <xsl:preserve-space elements="a" xsl:use-attribute-sets="foo" />
    <xsl:strip-space elements="a" xsl:use-attribute-sets="foo"/>
  
    <xsl:variable name="x" >x</xsl:variable>
    <xsl:param name="y" >x</xsl:param>

</xsl:stylesheet>

