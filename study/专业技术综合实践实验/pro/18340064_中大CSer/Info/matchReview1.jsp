<%@ page language="java" import="java.util.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String ans = "";

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql = String.format("select * from reviewmatchinfo order by mdeadline desc");
		ResultSet rs = stmt.executeQuery(sql);
		ans = "{\"Matches\": [";
		int c = 0;
		while (rs.next()) {
			if (c != 0) ans += ", ";
			c++;
			ans += "{\"Title\": \"" + rs.getString("mtitle") + 
						"\", \"ID\": \"" + rs.getString("mid") + 
						"\", \"Date\": \"" + rs.getString("mdate") + 
						"\", \"Deadline\": \"" + rs.getString("mdeadline") + 
						"\", \"Member\": \"" + rs.getString("mmember") + 
						"\", \"Link\": \"" + rs.getString("mlink") + "\"}";
		}
		ans += "], \"Status\": 200, \"Msg\": \"Successful!\"}";
		out.print(ans);
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>