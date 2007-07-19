<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0"
	    xmlns:user="http://mycompany.com/mynamespace" >
<variable name="meth" select="xml"/>
<variable name="dec" select="yes"/>
<variable name="ind" select="yes"/> 

<output method="xml" encoding="unicode" omit-xml-declaration="yes"/>  
<template match="/"> 
<user:br/>
	<user:div>text
 
<copy-of select="/xslTutorial"/> <user:br/> </user:div>
</template> 

</stylesheet>  
