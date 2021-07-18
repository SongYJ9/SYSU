<%@ page language="java" import="java.util.*, java.io.*" pageEncoding="utf-8" contentType="text/html; charset=utf-8" %>
<% 
	String course = (String) session.getAttribute("course");
	String id = session.getId();
%>

<!DOCTYPE HTML>
<html>
<head>
	<title>Session Y</title>
</head>

<body>
	<h1>Session Y</h1>
	session ID: <%=id%><br><br>
	course: <%=course%><br><br>
	<a href="X18340146.jsp">X.jsp</a><br><br>
	<a href="Z18340146.jsp">Z.jsp</a><br><br>
</body>
</html>
