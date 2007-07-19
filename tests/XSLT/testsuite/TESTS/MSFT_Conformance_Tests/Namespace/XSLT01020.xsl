<?xml version='1.0'?>
<十日本:stylesheet xmlns:十日本="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <十日本:template match="/">
    <HTML>
      <BODY>
       
          <十日本:for-each select="bookstore/magazine">
		<十日本:sort select="@frequency"/>
		<十日本:sort select="title"/>
         <十日本:value-of  select="title"/> is a <十日本:value-of select="@style"/> magazine published <十日本:value-of select="@frequency"/> 


         </十日本:for-each> 
	      
      </BODY>
    </HTML>
  </十日本:template>
</十日本:stylesheet>
