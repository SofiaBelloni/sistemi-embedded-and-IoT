package it.unibo.dammobileapp;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SwitchCompat;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.UUID;

import it.unibo.dammobileapp.btLib.BluetoothChannel;
import it.unibo.dammobileapp.btLib.BluetoothUtils;
import it.unibo.dammobileapp.btLib.ConnectToBluetoothServerTask;
import it.unibo.dammobileapp.btLib.ConnectionTask;
import it.unibo.dammobileapp.btLib.exceptions.BluetoothDeviceNotFound;
import it.unibo.dammobileapp.utils.Config;


public class MainActivity extends AppCompatActivity {
    private BluetoothChannel btChannel;
    private HttpCommunication httpCommunication;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), Config.bluetooth.ENABLE_BT_REQUEST);
        }

        /*

         */
        this.httpCommunication = new HttpCommunicationImpl(this, Config.URL, new DamManagerImpl(this));



        /*
        Thread to send Http requests to the server. Send the requests every 2 seconds.
         */
        new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                while(true){
                    try {
                        httpCommunication.sendRequest(new JSONObject("{\"command\":\"get_last_detection\"}"));
                        httpCommunication.sendRequest(new JSONObject("{\"command\":\"get_dam_opening\"}"));
                        Thread.sleep(2000);
                    } catch (InterruptedException | JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();


        initUI();
    }

    private void initUI() {
        findViewById(R.id.connectBtn).setOnClickListener(v -> {
            try {
                connectToBTServer();
            } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                bluetoothDeviceNotFound.printStackTrace();
            }
        });

        /*
        These are the buttons to send the dam opening percentage
         */
        findViewById(R.id.button0).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":0}");
        });
        findViewById(R.id.button20).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":20}");
        });
        findViewById(R.id.button40).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":40}");
        });
        findViewById(R.id.button60).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":60}");
        });
        findViewById(R.id.button80).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":80}");
        });
        findViewById(R.id.button100).setOnClickListener(v -> {
            btChannel.sendMessage("{\"command\":\"set_dam_opening\",\"dam_opening\":100}");
        });


        /*
        This is the switch for the manual mode
         */
        SwitchCompat manualSwitch = findViewById(R.id.mode);
        manualSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                //If manual mode is turned on enable all buttons and send set_mode MANUAL to the server
                if(isChecked){
                    btChannel.sendMessage("{\"command\":\"set_mode\",\"mode\":\"MANUAL\"}");
                    findViewById(R.id.button0).setEnabled(true);
                    findViewById(R.id.button20).setEnabled(true);
                    findViewById(R.id.button40).setEnabled(true);
                    findViewById(R.id.button60).setEnabled(true);
                    findViewById(R.id.button80).setEnabled(true);
                    findViewById(R.id.button100).setEnabled(true);

                } else{ //If manual mode is turned off disable all buttons and send set_mode AUTO to the server
                    btChannel.sendMessage("{\"command\":\"set_mode\",\"mode\":\"AUTO\"}");
                    findViewById(R.id.button0).setEnabled(false);
                    findViewById(R.id.button20).setEnabled(false);
                    findViewById(R.id.button40).setEnabled(false);
                    findViewById(R.id.button60).setEnabled(false);
                    findViewById(R.id.button80).setEnabled(false);
                    findViewById(R.id.button100).setEnabled(false);
                }
            }
        });



    }
    @Override
    protected void onStop() {
        super.onStop();

        btChannel.close();
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(Config.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        // !!! UTILIZZARE IL CORRETTO VALORE DI UUID
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(Config.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                ((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                findViewById(R.id.connectBtn).setEnabled(false);

                btChannel = channel;
            }

            @Override
            public void onConnectionCanceled() {
                ((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : unable to connect, device %s not found!",
                        Config.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));
            }
        }).execute();
    }
}