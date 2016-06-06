package com.mikefilion.hueapp.Hue;

import android.os.AsyncTask;
import android.support.design.widget.Snackbar;
import android.view.View;

/**
 * Created by mfilion on 2016-05-03.
 */
public class LinkButtonErrorNotification extends AsyncTask<Void, Void, Boolean> {
    private final View mView;

    public LinkButtonErrorNotification(View view) {
        mView = view;
    }
    /**
     * Override this method to perform a computation on a background thread. The
     * specified parameters are the parameters passed to {@link #execute}
     * by the caller of this task.
     * <p/>
     * This method can call {@link #publishProgress} to publish updates
     * on the UI thread.
     *
     * @param params The parameters of the task.
     * @return A result, defined by the subclass of this task.
     * @see #onPreExecute()
     * @see #onPostExecute
     * @see #publishProgress
     */
    @Override
    protected Boolean doInBackground(Void... params) {
        Snackbar.make(mView, "Link button not pressed", Snackbar.LENGTH_LONG).setAction("Action", null).show();
        return true;
    }
}
