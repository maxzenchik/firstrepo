package dbConnector;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
public class ConnectorMySQL {
	public static void main(String [] args) throws SQLException
	{
		String url = "jdbc:mysql://localhost/world?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
		String user = "root";
		String pass = "dave2302387";
		try{
		Connection con = DriverManager.getConnection(url, user, pass);
		System.out.println("success");
		String query = "SELECT * FROM city WHERE Population >= 5000000";
		Statement stmt = con.createStatement(); 
		ResultSet rs = stmt.executeQuery(query);
		while (rs.next())
		{
			System.out.println(rs.getString("Name"));
		}
		}
		catch(SQLException e)
		{
			System.err.println(e);
		}
	}
}
