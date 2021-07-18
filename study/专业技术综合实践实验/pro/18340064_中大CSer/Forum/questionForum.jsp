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
		String sql = String.format("select * from post where ptype = '0' order by pdate desc");
		ResultSet rs = stmt.executeQuery(sql);
		int c = 0;
		ans = "{\"Post\": [";
		while (rs.next()) {
			if (c != 0) ans += ", ";
			c++;
			ans += "{\"ID\": \"" + rs.getString("pid") + 
						"\", \"Name\": \"" + rs.getString("pname") + 
						"\", \"Title\": \"" + rs.getString("ptitle") + 
						"\", \"ImagePath\": \"" + "../images/1.png" + 
						"\", \"Content\": \"" + rs.getString("pcontent") + 
						"\", \"Date\": \"" + rs.getString("pdate") + 
						"\", \"Comment\": \"" + rs.getString("pcomment") + 
						"\", \"Like\": \"" + rs.getString("plike") + 
						"\", \"Favor\": \"" + rs.getString("pfavor") + "\"}";
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