<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <!-- Zero testing -->
        <zero1><xsl:value-of select="format-number(0.0, '#.#')"/></zero1>
        <zero2><xsl:value-of select="format-number(0000000000.0000000000, '#')"/></zero2>
        <zero3><xsl:value-of select="format-number(.0, '0.0')"/></zero3>
        <zero4><xsl:value-of select="format-number(00, '.0')"/></zero4>
        <zero5><xsl:value-of select="format-number(.001, '.#')"/></zero5>
        <zero6><xsl:value-of select="format-number(.001, '.##')"/></zero6>
        <zero7><xsl:value-of select="format-number(-0.0, '0.0;-0.0')"/></zero7>

        <!-- NaN testing -->        
        <nan1><xsl:value-of select="format-number(0.0 div 0.0, '(#)')"/></nan1>
        <nan2><xsl:value-of select="format-number(-0.0 div 0.0, '();-()')"/></nan2>

        <!-- Infinity testing -->        
        <inf1><xsl:value-of select="format-number(1.0 div 0.0, '(#)')"/></inf1>
        <inf2><xsl:value-of select="format-number(1.0 div 0.0, '')"/></inf2>
        <inf3><xsl:value-of select="format-number(1.0 div 0.0, 'Positive ')"/></inf3>
        <inf4><xsl:value-of select="format-number(-1.0 div 0.0, '(#);-(#)')"/></inf4>
        <inf5><xsl:value-of select="format-number(-1.0 div 0.0, 'Positive ;Negative ')"/></inf5>

        <!-- # symbol -->
        <digit1><xsl:value-of select="format-number(0.09999000, '--#.#--')"/></digit1>
        <digit2><xsl:value-of select="format-number(1.111, '.#')"/></digit2>
        <digit3><xsl:value-of select="format-number(0.99999999999999999999, '.#')"/></digit3>
        <digit4><xsl:value-of select="format-number(.01, '.#####')"/></digit4>
        <digit5><xsl:value-of select="format-number(1.0, '########################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################')"/></digit5>

        <!-- 0 symbol -->
        <zdigit1><xsl:value-of select="format-number(10.59, '0.0')"/></zdigit1>
        <zdigit2><xsl:value-of select="format-number(.05, '0.0')"/></zdigit2>
        <zdigit3><xsl:value-of select="format-number(10.99, '0.0')"/></zdigit3>
        <zdigit4><xsl:value-of select="format-number(00100.00100, '0000000000.0000000000')"/></zdigit4>
        <zdigit1><xsl:value-of select="format-number(1.0, '0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000')"/></zdigit1>
        <zdigit1><xsl:value-of select="format-number(5.001, '.000')"/></zdigit1>
        <zdigit1><xsl:value-of select="format-number(.59, '00')"/></zdigit1>

        <!-- . symbol -->
        <dec1><xsl:value-of select="format-number(1.1, '.')"/></dec1>
        <dec2><xsl:value-of select="format-number(1234.1234, '#.#.#.#.')"/></dec2>

        <!-- , symbol -->
        <group1><xsl:value-of select="format-number(1.1, ',')"/></group1>
        <group2><xsl:value-of select="format-number(1234, ',0')"/></group2>
        <group3><xsl:value-of select="format-number(1234.1234, ',,,')"/></group3>
        <group4><xsl:value-of select="format-number(1234.1234, '#.#,#,#,#')"/></group4>
        <group5><xsl:value-of select="format-number(1234567890.123456789, '#,,###,####.###,####')"/></group5>
        <group6><xsl:value-of select="format-number(300, '#,###')"/></group6>

        <!-- ; symbol -->
        <sep1><xsl:value-of select="format-number(-1, '0.0;-0.0')"/></sep1>
        <sep2><xsl:value-of select="format-number(-1, '0.0;(0.0);;;-0.0')"/></sep2>
        <sep3><xsl:value-of select="format-number(-1, '0.0;#.#')"/></sep3>
        <sep4><xsl:value-of select="format-number(-1, '0.0;')"/></sep4>
        <sep5><xsl:value-of select="format-number(-1, '0.0;;')"/></sep5>
        <sep6><xsl:value-of select="format-number(-1, '0.0;-0.0')"/></sep6>
        <sep7><xsl:value-of select="format-number(-12345.54321, '###,000.000###;-###,000.000###')"/></sep7>

        <!-- ' symbol -->
        <quote1><xsl:value-of select='format-number(4321.1234, "special chars: &#39;#0.,;&#39; number: #,###.### special chars: &#39;#0.,;&#39;&#39;#0.,;&#39;")'/></quote1>
        <quote2><xsl:value-of select='format-number(4321.1234, "&#39;hello&#39;##")'/></quote2>
        <quote3><xsl:value-of select='format-number(4321.1234, "#&#39;hello&#39;#")'/></quote3>
        <quote4><xsl:value-of select='format-number(4321.1234, "&#39;")'/></quote4>
        <quote5><xsl:value-of select='format-number(4321.1234, "&#39;##.##")'/></quote5>

        <!-- % symbol -->
        <percent1><xsl:value-of select='format-number(.9876543210, "0.##%")'/></percent1>
        <percent2><xsl:value-of select='format-number(98.76543210, "0.#%#")'/></percent2>
        <percent3><xsl:value-of select='format-number(.009, "#%")'/></percent3>
        <percent4><xsl:value-of select='format-number(.001, "#%")'/></percent4>
        <percent5><xsl:value-of select='format-number(.001, "0%")'/></percent5>
        <percent6><xsl:value-of select='format-number(.001, "%0")'/></percent6>

        <!-- per-mill symbol -->
        <permill1><xsl:value-of select="format-number(12.12, '0.0&#x2030;')"/></permill1>

        <!-- default minus sign -->
        <minus1><xsl:value-of select="format-number(-100, '')"/></minus1>

        <!-- combination -->
        <combo1><xsl:value-of select="format-number(.1, '.00##')"/></combo1>
        <combo2><xsl:value-of select="format-number(.123, '.00##')"/></combo2>
        <combo3><xsl:value-of select="format-number(.1234499999, '.00##')"/></combo3>
        <combo4><xsl:value-of select="format-number(.0001, '.00##')"/></combo4>
        <combo5><xsl:value-of select="format-number(.99999, '.00##')"/></combo5>
        <combo6><xsl:value-of disable-output-escaping="yes" select="format-number(1234.4321, '--&gt;##0,000,000.00##&lt;--')"/></combo6>

        <!-- unusual -->
        <unusual1><xsl:value-of select="format-number(10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, ',###')"/></unusual1>
        <unusual2><xsl:value-of select="format-number(.00000000000000000012345678901234567890123456789000, '17: #.###################################')"/></unusual2>
        <unusual3><xsl:value-of select="format-number(.00000000000000000001234567890123456789012345678900, '16: #.###################################')"/></unusual3>
        <unusual4><xsl:value-of select="format-number(.00000000000000000000123456789012345678901234567890, '15: #.###################################')"/></unusual4>

    </xsl:template>

</xsl:stylesheet>
