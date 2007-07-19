<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml"/>  <!-- Pri 0 method="xml" -->

    <xsl:output cdata-section-elements="cdata1"/>

    <!-- Include stylesheet that imports inc/import-out.inc multiple times -->
    <xsl:include href="inc/include-out.inc"/>

    <xsl:output encoding="unknown"/>  <!-- Pri 0 encoding="unknown" -->

    <xsl:output encoding="UTF-8"/>  <!-- Pri 0 encoding="UTF-8" overrides "unknown" -->

    <xsl:output cdata-section-elements="cdata3"/>

    <xsl:template match="/">
        <html>
            <cdata1>Text should come out in CDATA section</cdata1>
            <cdata2>Text should come out in CDATA section</cdata2>
            <cdata3>Text should come out in CDATA section</cdata3>
            <br/>
        </html>
    </xsl:template>

</xsl:stylesheet>
