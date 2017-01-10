package comon.example.finaly;

import java.sql.Connection;
import java.sql.DriverManager;
//import java.sql.Connection;
//import java.sql.DriverManager;
//import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Driver;
//import java.sql.Statement;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
public class MainActivity extends Activity {

	static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		// getMenuInflater().
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	public void sendMessage(View view) {
		Intent intent = new Intent(this, DisplayMessageActivity.class);
		EditText editText = (EditText) findViewById(R.id.edit_message);
		String message = editText.getText().toString();
		intent.putExtra(EXTRA_MESSAGE, message);
		startActivity(intent);

	}

	public void copyMessage(View view) {
		EditText editText = (EditText) findViewById(R.id.edit_message);
		editText.setText("ggwp lol");
	}

	public void FindCountry(View view) throws SQLException, InstantiationException, IllegalAccessException, ClassNotFoundException {
		EditText editText = (EditText) findViewById(R.id.edit_message);
		try {
			
			String url = "jdbc:mysql://localhost:3306/world";
			Connection con = DriverManager.getConnection(url, "root", "dave2302387");
			Connection conbo = DriverManager.getConnection("jdbc:mysql://localhost/world?" +
                    "user=root&password=dave2302387");
			
		} catch (SQLException e) {
			editText.setText(e.toString());
			
		}
		
		// editText.setText("success");

	}
}
