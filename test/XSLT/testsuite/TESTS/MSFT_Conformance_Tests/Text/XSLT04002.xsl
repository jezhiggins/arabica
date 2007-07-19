<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <p>
            <xsl:text xmlns:NS1="http://www.w3.org/XML/1998/namespace" NS1:space="preserve">
There is an enter after the end of this line
There are s p a c e s in here.
There is a new line feed here
There is tab here	End of the text.
</xsl:text>
        </p>
    </xsl:template>
</xsl:stylesheet>
