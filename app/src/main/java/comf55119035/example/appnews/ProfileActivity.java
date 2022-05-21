package comf55119035.example.appnews;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;


public class ProfileActivity extends AppCompatActivity {

    ListView listView;
    String mTitle[] = {"I Gusti Ngurah Putu Satya Wibawa", "Dian Pratama Putri", "Nita Wulandari", "Arif Rahmawan", "Nandana Niranjana"};
    String mDescription[] = {"F55119002", "F55119004", "F55119009", "F55119031", "F55119035"};
    int images[] = {R.drawable.satya1, R.drawable.dian, R.drawable.nita, R.drawable.arif, R.drawable.nanda};
    // so our images and other things are set in array

    // now paste some images in drawable


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        listView = findViewById(R.id.listView);
        // now create an adapter class

        MyAdapter adapter = new MyAdapter(this, mTitle, mDescription, images);
        listView.setAdapter(adapter);
        // there is my mistake...
        // now again check this..

        // now set item click on list view
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (position ==  0) {
                    Toast.makeText(ProfileActivity.this, "I Gusti Ngurah Putu Satya Wibawa - F55119002", Toast.LENGTH_SHORT).show();
                }
                if (position ==  1) {
                    Toast.makeText(ProfileActivity.this, "Dian Pratama Putri - F55119004", Toast.LENGTH_SHORT).show();
                }
                if (position ==  2) {
                    Toast.makeText(ProfileActivity.this, "Nita Wulandari - F55119009", Toast.LENGTH_SHORT).show();
                }
                if (position ==  3) {
                    Toast.makeText(ProfileActivity.this, "Arif rahmawan - F55119031", Toast.LENGTH_SHORT).show();
                }
                if (position ==  4) {
                    Toast.makeText(ProfileActivity.this, "Nandana Niranjana - F55119035", Toast.LENGTH_SHORT).show();
                }
            }
        });
        // so item click is done now check list view
    }

    class MyAdapter extends ArrayAdapter<String> {

        Context context;
        String rTitle[];
        String rDescription[];
        int rImgs[];

        MyAdapter (Context c, String title[], String description[], int imgs[]) {
            super(c, R.layout.row, R.id.textView1, title);
            this.context = c;
            this.rTitle = title;
            this.rDescription = description;
            this.rImgs = imgs;

        }

        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            LayoutInflater layoutInflater = (LayoutInflater)getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View row = layoutInflater.inflate(R.layout.row, parent, false);
            ImageView images = row.findViewById(R.id.image);
            TextView myTitle = row.findViewById(R.id.textView1);
            TextView myDescription = row.findViewById(R.id.textView2);

            // now set our resources on views
            images.setImageResource(rImgs[position]);
            myTitle.setText(rTitle[position]);
            myDescription.setText(rDescription[position]);




            return row;
        }
    }
}