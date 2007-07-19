<?xml version="1.0"?>
<ped:transform xmlns:ped="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres09 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 Conflict Resolution for Template rules. -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Verify that template with higher priority executes, and that
  	   one with a lower import precedence does not. -->

<ped:import href="k.xsl"/>
<ped:include href="l.xsl"/>
<ped:output method="xml"/>

<ped:template match="doc">
  <out>
    <ped:value-of select="'Testing '"/>
    <ped:for-each select="*">
      <ped:value-of select="."/><ped:text> </ped:text>		
    </ped:for-each>
  </out>
</ped:template>

</ped:transform>
