<?xml version='1.0'?>
<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0">

<output method="xml" omit-xml-declaration="yes" indent="yes"/>

 <template match="/">
  <for-each select="//fruit">
	<sort select="child::elem/@a" data-type="number" /> 
	<value-of select="@name" /> :  <value-of select="elem/@a" 
/> 
  </for-each>

 </template>
 </stylesheet>
