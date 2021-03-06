package com.mcs.robot;

import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.appindexing.Thing;
import com.google.android.gms.common.api.GoogleApiClient;

import java.io.IOException;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, AddSound.NewSound {


    private static final String DIALOG = "tag_dialog";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private String path;
    private boolean inrecord = false;
    private boolean isTest = false;
    private FloatingActionButton fab;
    private TextView tv;
    private MediaRecorder recorder;
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        path = Environment.getExternalStorageDirectory().getAbsolutePath();// + "/PROJET_MCS";
        Log.w(path, path);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);


        fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(this);
        findViewById(R.id.saveb).setOnClickListener(this);
        findViewById(R.id.corpusb).setOnClickListener(this);

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    public Action getIndexApiAction() {
        Thing object = new Thing.Builder()
                .setName("Main Page") // TODO: Define a title for the content shown.
                // TODO: Make sure this auto-generated URL is correct.
                .setUrl(Uri.parse("http://[ENTER-YOUR-URL-HERE]"))
                .build();
        return new Action.Builder(Action.TYPE_VIEW)
                .setObject(object)
                .setActionStatus(Action.STATUS_TYPE_COMPLETED)
                .build();
    }

    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        AppIndex.AppIndexApi.start(client, getIndexApiAction());
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        AppIndex.AppIndexApi.end(client, getIndexApiAction());
        client.disconnect();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.saveb: {
                AddSound dialogAddItem = new AddSound();
                dialogAddItem.show(getSupportFragmentManager(), DIALOG);
                // on crée un callback entre l'activité et le Dialog, voir la définition du callback
                // dans la classe DialogAddItem
                dialogAddItem.setCallback(this);
                break;
            }

            case R.id.corpusb: {
                break;
            }
            case R.id.fab: {
                if (inrecord && !isTest) {
                    findViewById(R.id.linearb).setVisibility(View.VISIBLE);
                    fab.setImageResource(R.drawable.ic_micro);
                    stopRecord();
                    inrecord = false;
                    Toast.makeText(this, "Enregistrement Terminé", Toast.LENGTH_SHORT).show();
                } else if (inrecord && isTest) {
                    stopRecord();
                    fab.setImageResource(R.drawable.ic_micro);
                    inrecord = false;
                    isTest = false;
                    //on teste on affiche le resulat
                    tv.setText("Resultat du test:");
                    //on suprime temp
                    deleteFile(path + "/temp.wav");
                } else {
                    startRecord(path + "/temp.wav");
                    inrecord = true;
                    isTest = true;
                    fab.setImageResource(R.drawable.ic_stop);
                }
                break;
            }
        }
    }

    @Override
    public void itemWasCreated(TypeAction action) {
        findViewById(R.id.linearb).setVisibility(View.GONE);
        fab.setImageResource(R.drawable.ic_stop);
        Toast.makeText(this, "Enregistrement en cours", Toast.LENGTH_SHORT).show();
        startRecord(path + "/" + action.toString() + ".wav");

    }

    private void startRecord(String file) {
        try {
            recorder = new MediaRecorder();
            recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
            recorder.setOutputFormat(MediaRecorder.OutputFormat.DEFAULT); //on a pas trouvé le .wav
            recorder.setAudioEncoder(MediaRecorder.AudioEncoder.DEFAULT);
            recorder.setOutputFile(file);
            recorder.prepare();
            recorder.start();
            inrecord = true;
        } catch (IOException e) {
            Toast.makeText(this, "Erreur lors de la preparation du recorder", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        } catch (Throwable t) {
            Toast.makeText(this, "Erreur lors du lancement de l'enregistrement", Toast.LENGTH_SHORT).show();
            t.printStackTrace();
        }
    }

    private void stopRecord() {
        recorder.stop();
        recorder.reset();
        recorder.release();
    }
}
