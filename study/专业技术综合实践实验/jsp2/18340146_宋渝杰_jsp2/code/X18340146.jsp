<%@ page language="java" import="java.util.*, java.io.*" pageEncoding="utf-8" contentType="text/html; charset=utf-8" %>
<% 
	session.setAttribute("course", "移动Web应用设计" + " --- " + new Date());
	String id = session.getId();
%>

<!DOCTYPE HTML>
<html>
<head>
	<title>Session X</title>
</head>

<body>
	<h1>Session X</h1>
	session ID: <%=id%><br><br>
	<a href="Y18340146.jsp">Y.jsp</a><br><br>
	<a href="Z18340146.jsp">Z.jsp</a>
</body>
</html>