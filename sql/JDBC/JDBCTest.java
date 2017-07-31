


import java.sql.*;
import java.sql.Connection;
import java.sql.DriverManager;

class JDBCTest
{
	private static final String url = "jdbc:mysql://localhost:3306/test_db?autoReconnect=true&useSSL=false";
	private static final String user = "wallace";
	private static final String password = "";
  
	public static void main(String args[])
	{
		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
			System.out.println("Success: Found Driver");
	  
			// You can have user and password. 
			Connection con = DriverManager.getConnection(url, user, password);

			// You can ignore the user. 
//			Connection con = DriverManager.getConnection(url);

			System.out.println("Success: Get Connection Object con");
    
			// String SQL = "select * from /var/lib/mysql/pchendb";
			Statement stmt = con.createStatement();
			System.out.println("Success: Create Statement Object stmt");
			String SQL = "select * from Persons";
			ResultSet rs = stmt.executeQuery(SQL);
			System.out.println("Success: Create ResultSet Object rs");

			while (rs.next()) 
			{
				System.out.println("  Sucess rs.next: "+ rs.getString(1) + " " + rs.getString(2));
			}
		} 

		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
}