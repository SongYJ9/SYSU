<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String ID = request.getParameter("ID");
	String Name = request.getParameter("Name");
	String Action = request.getParameter("Action");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql = String.format("select * from reviewjobinfo where jid = '%s'", ID);
		ResultSet rs = stmt.executeQuery(sql);
		if (rs.next()) {
			if (Action.equals("1")) {
				String s1 = rs.getString("jtitle");
				String sql2 = String.format("insert into jobinfo values('%s', '%s', '%s', '%s', '%s', '%s')", 
							s1, rs.getString("jdate"), rs.getString("jdeadline"), rs.getString("jmember"), rs.getString("jwage"), rs.getString("jlink"));
				int cnt = stmt.executeUpdate(sql2);
				if (cnt > 0) {
					sql2 = String.format("delete from reviewjobinfo where jid = '%s'", ID);
					int cnt2 = stmt.executeUpdate(sql2);
					if (cnt2 > 0) {
						java.util.Date dNow = new java.util.Date();
						SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
						String str_date = ft.format(dNow);
						String sql3 = String.format("insert into operations values('%s', '%s', '%s', '%s')", 
									Name, "Agree ^_^", s1, str_date);
						int cnt3 = stmt.executeUpdate(sql3);
						if (cnt3 > 0)
							out.print("{\"Status\": 200, \"Msg\": \"Successful!\"}");
						else
							out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
					}
					else
						out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
				}
				else
					out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
			}
			else {
				String s1 = rs.getString("jtitle");
				String sql2 = String.format("delete from reviewjobinfo where jid = '%s'", ID);
				int cnt = stmt.executeUpdate(sql2);
				if (cnt > 0) {
					java.util.Date dNow = new java.util.Date();
					SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					String str_date = ft.format(dNow);
					String sql3 = String.format("insert into operations values('%s', '%s', '%s', '%s')", 
								Name, "Disagree >_<", s1, str_date);
					int cnt2 = stmt.executeUpdate(sql3);
					if (cnt2 > 0)
						out.print("{\"Status\": 200, \"Msg\": \"Successful!\"}");
					else
						out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
				}
				else
					out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
			}
		}
		else
			out.print("{\"Status\": 400, \"Msg\": \"No match!\"}");
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>