<!-- Error Case -->
<x xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:for-each select="bookstore">
        <xsl:sort lang="invalid"/>
    </xsl:for-each>
</x>
