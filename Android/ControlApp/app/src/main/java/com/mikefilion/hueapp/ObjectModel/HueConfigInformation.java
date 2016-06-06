package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueConfigInformation {
    public HueConfigInformation(JSONObject value) {
        try {
            zigbeechannel = value.getInt("zigbeechannel");
            proxyport = value.getInt("proxyport");
            dhcppublic = value.getBoolean("dhcppublic");
            linkbutton = value.getBoolean("linkbutton");
            portalservices = value.getBoolean("portalservices");
            factorynew = value.getBoolean("factorynew");
            name = value.getString("name");
            bridgeid = value.getString("bridgeid");
            mac = value.getString("mac");
            ipaddress = value.getString("ipaddress");
            netmask = value.getString("netmask");
            gateway = value.getString("gateway");
            proxyaddress = value.getString("proxyaddress");
            UTC = value.getString("UTC");
            localtime = value.getString("localtime");
            timezone = value.getString("timezone");
            modelid = value.getString("modelid");
            swversion = value.getString("swversion");
            apiversion = value.getString("apiversion");
            portalconnection = value.getString("portalconnection");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    int zigbeechannel;
    int proxyport;
    boolean dhcppublic;
    boolean linkbutton;
    boolean portalservices;
    boolean factorynew;
    String name;
    String bridgeid;
    String mac;
    String ipaddress;
    String netmask;
    String gateway;
    String proxyaddress;
    String UTC;
    String localtime;
    String timezone;
    String modelid;
    String swversion;
    String apiversion;
    String portalconnection;
}
