<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
     <out> 
         <xsl:attribute name="xmlns:xsl" namespace="whatever">http://www.w3.org/1999/XSL/Transform</xsl:attribute>
     </out>
</xsl:template>

</xsl:stylesheet>