package com.mikefilion.hueclientapp;

public class CardData {

    String name;
    String email;
    int image;
    int id_;

    public CardData(String name, String email, int image, int id_) {
        this.name = name;
        this.email = email;
        this.image = image;
        this.id_ = id_;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public int getImage() {
        return image;
    }

    public int getId() {
        return id_;
    }
}