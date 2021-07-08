package com.top.imebra;

import android.content.Context;
import android.graphics.Bitmap;
import android.net.Uri;

import com.imebra.CodecFactory;
import com.imebra.ColorTransformsFactory;
import com.imebra.DataSet;
import com.imebra.DrawBitmap;
import com.imebra.Image;
import com.imebra.Memory;
import com.imebra.PipeStream;
import com.imebra.StreamReader;
import com.imebra.TransformsChain;
import com.imebra.VOILUT;
import com.imebra.drawBitmapType_t;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class DicomLoader {

    // 私有构造
    private DicomLoader() {
    }

    private static DicomLoader single = null;

    public static DicomLoader getInstance() {
        if (single == null) {
            single = new DicomLoader();
        }
        return single;
    }

    public List<Bitmap> loader(Context context, Uri uri) {
        CodecFactory.setMaximumImageSize(8000, 8000);
        List<Bitmap> list = new ArrayList<>();

        try {
            InputStream inputStream = context.getContentResolver().openInputStream(uri);
            PipeStream imebraPipe = new PipeStream(32000);

            Thread pushThread = new Thread(new PushToImebraPipe(imebraPipe, inputStream));
            pushThread.start();

            DataSet loadDataSet = CodecFactory.load(new StreamReader(imebraPipe.getStreamInput()));

            DicomEntity dicomEntity = DicomEntity.convert(loadDataSet);

            for (int i = 0; i < dicomEntity.getNumberOfFrames(); i++) {
                Bitmap bitmap = getBitmap(loadDataSet, i);
                list.add(bitmap);
            }


        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        return list;
    }

    private Bitmap getBitmap(DataSet dataSet, int index) {
        Image dicomImage = dataSet.getImageApplyModalityTransform(index);
        TransformsChain chain = new TransformsChain();
        if (ColorTransformsFactory.isMonochrome(dicomImage.getColorSpace())) {
            VOILUT voilut = new VOILUT(VOILUT.getOptimalVOI(
                    dicomImage,
                    0, 0, dicomImage.getWidth(), dicomImage.getHeight()
            ));
            chain.addTransform(voilut);
        }
        DrawBitmap drawBitmap = new DrawBitmap(chain);
        Memory memory = drawBitmap.getBitmap(dicomImage, drawBitmapType_t.drawBitmapBGRA, 4);
        Bitmap renderBitmap = Bitmap.createBitmap((int) dicomImage.getWidth(), (int) dicomImage.getHeight(), Bitmap.Config.ARGB_8888);
        byte[] memoryByte = new byte[(int) memory.size()];
        memory.data(memoryByte);
        ByteBuffer byteBuffer = ByteBuffer.wrap(memoryByte);
        renderBitmap.copyPixelsFromBuffer(byteBuffer);
        return renderBitmap;
    }

}
