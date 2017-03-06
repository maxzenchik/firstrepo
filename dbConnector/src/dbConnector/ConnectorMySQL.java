package dbConnector;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import dbConnector.City;
public class ConnectorMySQL {
    private	static String url = "jdbc:mysql://localhost/world?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
    private static String user = "root";
    private static String pass = "dave2302387";


	public static void ConnectDB()
	{
		try
		{
		Connection con = DriverManager.getConnection(url, user, pass);
		
		System.out.println("success");
		
		String select_query = "SELECT * FROM city WHERE Population > 9000000";
		Statement stmt = con.createStatement(); 
		//stmt.executeUpdate(insert_query);
		ResultSet rs = stmt.executeQuery(select_query);
		City MyCity = new City();
		MyCity.setPopulation(3000000);
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
