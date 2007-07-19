<xsl2 xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Should not recognize old namespace during include -->
<xtl:value-of xmlns:xtl="http://www.w3.org/TR/WD-xsl" select="."/>

<!-- Change prefix specifying XSL namespace -->
<xslt:apply-templates xmlns:xslt="http://www.w3.org/1999/XSL/Transform"/>
</xsl2>