<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <!-- Lesson. Note how the initial context node  
is reduced by the apply templates; this stops  
the 'leaking' of content when all I want is  
a subset of the whole in the result tree -->
	<root>
        <xsl:apply-templates select="//me"></xsl:apply-templates>
	<xsl:apply-templates select="/xslTutorial/doc[1]/gf[1]/par[1]/me[1]" mode="value-test"></xsl:apply-templates>
	</root>
    </xsl:template>
    <xsl:template match="br">
        <br></br>
    </xsl:template>
    <xsl:template match="me" priority="10">
        <html>
            <head>
                <title>
                    <xsl:text> Document</xsl:text>
                </title>
            </head>
            <body>
                <H2>Descendant or Self Axis</H2>
                <b>
                    <xsl:apply-templates select="descendant-or-self::*/p"></xsl:apply-templates>
                </b>
                <H2>Descendant Axis</H2>
                <b>
                    <xsl:apply-templates select="descendant::*/p"></xsl:apply-templates>
                </b>
                <H2>Self Axis</H2>
                <b>
                    <xsl:apply-templates select="self::*/p"></xsl:apply-templates>
                </b>
                <H2>Child Axis</H2>
                <b>
                    <xsl:apply-templates select="child::*/p"></xsl:apply-templates>
                </b>
                <H2>Attribute Axis</H2>
                <b>
                    <xsl:apply-templates select="attribute::*"></xsl:apply-templates>
                </b>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="me" mode="value-test">
                <H2>value of .</H2>
                <b>
                    <xsl:value-of select="."></xsl:value-of>
                </b>
                <H2>value of ..</H2>
                <b>
                    <xsl:value-of select=".."></xsl:value-of>
                </b>
    </xsl:template>
</xsl:stylesheet>
