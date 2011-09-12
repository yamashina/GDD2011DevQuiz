package com.yamashina.android.codegetter;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;
import com.google.android.apps.gddquiz.IQuizService;

public class CodeGetter extends Activity {
	final static String TAG = "GDDCodeGetter";
	private IQuizService service;
    private Button bindButton;
    private Button unbindButton;
	private Button getButton;
	
    private ServiceConnection conn = new ServiceConnection() {
    	@Override
        public void onServiceConnected(ComponentName componentName, IBinder binder) {
    		Log.d(TAG, "onServiceConnected");
        	service = IQuizService.Stub.asInterface(binder);
            setButtonEnabled(getButton, true);
            setButtonEnabled(unbindButton, true);
        }

    	@Override
        public void onServiceDisconnected(ComponentName componentName) {
    		Log.d(TAG, "onServiceDisconnected");
    		service = null;
            setButtonEnabled(bindButton, true);
            setButtonEnabled(unbindButton, false);
            setButtonEnabled(getButton, false);
        }
    };

    private OnClickListener bindListener = new OnClickListener() {
        public void onClick(View view) {
            setButtonEnabled(bindButton, false);
            Intent intent = new Intent(IQuizService.class.getName());
            bindService(intent, conn, BIND_AUTO_CREATE);
        }
    };

    private OnClickListener unbindListener = new OnClickListener() {
        public void onClick(View view) {
            unbind();
        }
    };
    
    private OnClickListener getListener = new OnClickListener() {
        public void onClick(View view) {
			try {
				String code = service.getCode();
				Log.d(TAG, code);
				Toast.makeText(CodeGetter.this, code, Toast.LENGTH_LONG).show();
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}			
        }
    };

   /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        bindButton = (Button)findViewById(R.id.bind_button);
        bindButton.setOnClickListener(bindListener);

        unbindButton = (Button) findViewById(R.id.unbind_button);
        unbindButton.setOnClickListener(unbindListener);

        getButton = (Button) findViewById(R.id.get_button);
        getButton.setOnClickListener(getListener);

        setButtonEnabled(unbindButton, false);
        setButtonEnabled(getButton, false);
    }
    
    @Override
    protected void onPause() {
        unbind();
        super.onPause();
    }
    
    private void setButtonEnabled(Button button, boolean enabled) {
        button.setEnabled(enabled);
        button.invalidate();
    }

    private void unbind() {
        setButtonEnabled(bindButton, true);
        setButtonEnabled(unbindButton, false);
        setButtonEnabled(getButton, false);
        unbindService(conn);
    }
}
