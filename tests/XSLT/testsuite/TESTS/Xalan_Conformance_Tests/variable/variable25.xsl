<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:txt="http://www.host.com/txt"
                exclude-result-prefixes="txt">

  <!-- FileName: variable25 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11 Variables and Parameters -->
  <!-- Purpose: Variable name is a QName. -->
  <!-- Author: Tommy Burglund -->

<xsl:variable name="txt:me" select="'Tommy'"/>

<xsl:template match="/">
 <out>
  <xsl:value-of select="$txt:me"/>
 </out>
</xsl:template>

</xsl:stylesheet>
