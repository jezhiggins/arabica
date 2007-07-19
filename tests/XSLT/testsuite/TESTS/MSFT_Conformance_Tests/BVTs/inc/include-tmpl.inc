<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Force resize of import tree -->
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>
    <xsl:import href="import-tmpl.inc"/>

    <!-- Make sure that templates within import2.inc override templates within import1 -->
    <xsl:import href="import-tmpl2.inc"/>

</xsl:stylesheet>  

