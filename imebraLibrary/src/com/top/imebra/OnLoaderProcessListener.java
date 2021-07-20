package com.top.imebra;

import android.graphics.Bitmap;

import java.io.FileNotFoundException;
import java.util.List;

public interface OnLoaderProcessListener {
    void onPreLoader(Bitmap bitmap);
    void onLoadAll(List<Bitmap> list);
    void onLoadError(FileNotFoundException e);
}
