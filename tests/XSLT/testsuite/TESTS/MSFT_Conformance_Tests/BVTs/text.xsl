<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <!-- whitespace -->
        <x><xsl:text>	Leading and trailing	 </xsl:text></x>
        <x><xsl:text xml:space="preserve">				 </xsl:text></x> <!-- pure whitespace -->
        <x><xsl:text xml:space="preserve"> </xsl:text></x>
        <x><xsl:text> </xsl:text></x>
        <x><xsl:text>         </xsl:text></x>

        <!-- disable-output-escaping -->
        <x><xsl:text>This is a test&lt;use entities&gt;</xsl:text></x>
        <x><xsl:text disable-output-escaping="no">This is a test&lt;use entities&gt;</xsl:text></x>
        <x><xsl:text disable-output-escaping="yes">This is a test&lt;use entities with disable-output-encoding&gt;</xsl:text></x>

        <!-- Use disable-output-escaping for text within attributes, PI's, comments -->
        <xsl:element name="foo">
            <xsl:attribute name="bar"><xsl:text disable-output-escaping="yes">disable-output-escaping="yes" should be ignored</xsl:text></xsl:attribute>
            <xsl:processing-instruction name="my-pi"><xsl:text disable-output-escaping="no">disable-output-escaping="no" should be ignored</xsl:text></xsl:processing-instruction>
            <xsl:comment><xsl:text disable-output-escaping="no">disable-output-escaping="no" should be ignored</xsl:text></xsl:comment>
        </xsl:element>

        <!-- Allow comments and PI's within xsl:text -->
        <x><xsl:text>   <!-- This is some text -->  <?my-pi This is a PI ?>    Here is some text   </xsl:text></x>

    </xsl:template>
</xsl:stylesheet>
