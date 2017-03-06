
package comon.example.finaly;
//для парсинга с сайта##############################################
import org.jsoup.select.*;

import java.io.IOException;
import java.util.ArrayList;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
//##################################################################
//import java.sql.Statement;
import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
public class MainActivity extends Activity {

	
    public Elements title;
    
    public ArrayList<String> titleList = new ArrayList<String>();
   
    private ArrayAdapter<String> adapter;
    
    private ListView lv;
	static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
	DatabaseWorker worker;
	SQLiteDatabase db;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // определение данных
        lv = (ListView) findViewById(R.id.listView1);
        // запрос к нашему отдельному поток на выборку данных
        new NewThread().execute();
        // Добавляем данные для ListView
        adapter = new ArrayAdapter<String>(this, R.layout.list_item, R.id.product_name, titleList);

		
		
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
		editText.setText("g1232134124");
	}

	public void FindCountry(View view) throws SQLException, InstantiationException, IllegalAccessException, ClassNotFoundException {
		EditText editText = (EditText) findViewById(R.id.edit_message);
		try {
			worker = new DatabaseWorker(this);
			db = worker.getReadableDatabase();
			
		
		} catch (SQLException e) {
			editText.setText(e.toString());
			
		}
		
		

	}
public class NewThread extends AsyncTask<String, Void, String>
{

	@Override
	protected String doInBackground(String... params) {
		// TODO Auto-generated method stub
		Document doc;
		try {
            // определяем откуда будем воровать данные
            //doc = Jsoup.connect("https://www.whoscored.com/LiveScores").userAgent("Mozilla/5.0 Gecko/20100101 Firefox/21.0").get();
            doc = Jsoup.connect("http://livesport.ws/live-football").get();
            //doc = Jsoup.connect("https://eu.battle.net/forums/ru/overwatch/19369455").get();
            // задаем с какого места, я выбрал заголовке статей
            title = doc.select("div.commands");
            
            
            
            //title = doc.getElementById("countdown");
            // чистим наш аррей лист для того что бы заполнить
            titleList.clear();
            int x = title.size();
            // и в цикле захватываем все данные какие есть на странице
            for (Element titles : title) {
                    // записываем в аррей лист
                    titleList.add(titles.text());
            }
    } catch (IOException e) {
            e.printStackTrace();
    }
		return null;
	}
    @Override
    protected void onPostExecute(String result) {

            // после запроса обновляем листвью
            lv.setAdapter(adapter);
    }
}
}
