<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/" mode="m">mode should be ignored
<div>
This Stylesheet is just a literal result element with no template matches
<span priority="10">as should priority</span>
<span version="2"/>
</div>
</xsl:template>
</xsl:stylesheet>