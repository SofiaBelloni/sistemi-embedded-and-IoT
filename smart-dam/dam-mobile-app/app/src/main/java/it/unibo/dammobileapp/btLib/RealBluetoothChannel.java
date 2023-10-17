package it.unibo.dammobileapp.btLib;

import android.bluetooth.BluetoothSocket;
import android.os.Message;
import android.util.Log;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import it.unibo.dammobileapp.btLib.utils.C;

public final class RealBluetoothChannel extends BluetoothChannel {

    private String remoteDeviceName;

    RealBluetoothChannel(BluetoothSocket socket){
        remoteDeviceName = socket.getRemoteDevice().getName();

        worker = new BluetoothWorker(socket);
        new Thread(worker).start();
    }

    @Override
    public String getRemoteDeviceName(){
        return remoteDeviceName;
    }


    class BluetoothWorker implements ExtendedRunnable {
        private final BluetoothSocket socket;
        private final InputStream inputStream;
        private final OutputStream outputStream;

        BluetoothWorker(BluetoothSocket socket) {
            this.socket = socket;

            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                tmpIn = socket.getInputStream();
            } catch (IOException e) {
                Log.e(C.LIB_TAG, "Error occurred when creating input stream", e);
            }
            try {
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
                Log.e(C.LIB_TAG, "Error occurred when creating output stream", e);
            }

            inputStream = tmpIn;
            outputStream = tmpOut;
        }

        public void run() {
            while (true) {
                try {
                    DataInputStream input = new DataInputStream(inputStream);

                    StringBuffer readbuffer = new StringBuffer();

                    byte inputByte;

                    while ((inputByte = input.readByte()) != 0) {
                        char chr = (char) inputByte;
                        if(chr != C.message.MESSAGE_TERMINATOR){
                            readbuffer.append(chr);
                        } else {
                            String inputString = readbuffer.toString();
                            Message receivedMessage = btChannelHandler.obtainMessage(C.channel.MESSAGE_RECEIVED, inputString.getBytes().length, -1, inputString.getBytes());
                            receivedMessage.sendToTarget();

                            readbuffer = new StringBuffer();
                        }
                    }
                }
                catch(Exception e){
                    e.printStackTrace();
                }
            }
        }

        public void write(byte[] bytes) {
            try {
                byte[] bytesToBeSent = Arrays.copyOf(bytes, bytes.length+1);
                bytesToBeSent[bytesToBeSent.length -1] = C.message.MESSAGE_TERMINATOR;

                outputStream.write(bytesToBeSent);

                Message writtenMsg = btChannelHandler.obtainMessage(C.channel.MESSAGE_SENT, -1, -1, bytes);
                writtenMsg.sendToTarget();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public void cancel() {
            try {
                socket.close();
            } catch (IOException e) {
                Log.e(C.LIB_TAG, "Could not close the connect socket", e);
            }
        }
    }
}
