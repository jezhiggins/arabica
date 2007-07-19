<?xml version="1.0"?>
<jad:transform xmlns:jad="http://www.w3.org/1999/XSL/Transform" version="1.0">
<jad:output method="xml"/>

  <!-- FileName: l -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.1 XSLT Namespace. -->
  <!-- Purpose: Included by other tests.  -->

<jad:template match="doc" priority="1.0">
  <out>
    <jad:value-of select="'In Include: Testing '"/>
    <jad:for-each select="*">
      <jad:value-of select="."/><jad:text> </jad:text>		
    </jad:for-each>
  </out>
</jad:template>

</jad:transform>