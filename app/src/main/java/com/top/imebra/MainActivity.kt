package com.top.imebra

import android.app.AlertDialog
import android.content.Intent
import android.graphics.Bitmap
import android.net.Uri
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.imebra.*
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import java.lang.Exception
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        System.loadLibrary("imebra_lib")

        setContentView(R.layout.activity_main)

    }

    fun loadDicomFileClicked(view: View) {
        val intent = Intent()
            .setType("*/*")
            .setAction(Intent.ACTION_GET_CONTENT)
        startActivityForResult(Intent.createChooser(intent, "Select a DICOM file"), 123)
    }

    var selectedfile: Uri? = null
    var count = 0;
    var framesCount: Long = -1;

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode == 123 && resultCode == RESULT_OK) {
            try {
                CodecFactory.setMaximumImageSize(8000, 8000)

                // Get the selected URI, then open an input stream
                selectedfile = (data!!.data ?: return)

                goToImg(count)

            } catch (e: IOException) {
                val dlgAlert = AlertDialog.Builder(this)
                dlgAlert.setMessage(e.message)
                dlgAlert.setTitle("Error")
                dlgAlert.setPositiveButton(
                    "OK"
                ) { dialog, which ->
                    //dismiss the dialog
                }
                dlgAlert.setCancelable(true)
                dlgAlert.create().show()
                val test = "Test"
            }
        }

    }

    fun pre(view: View) {
        if (count == 0) {
            count = framesCount.toInt()
        }
        --count

        goToImg(count)
    }

    fun next(view: View) {
        if (count + 1 == framesCount.toInt()) {
            count = -1
        }
        ++count
        goToImg(count)
    }


    fun goToImg(index: Int) {
        val stream = contentResolver.openInputStream(selectedfile!!)

        // The usage of the Pipe allows to use also files on Google Drive or other providers
        val imebraPipe = PipeStream(32000)

        // Launch a separate thread that read from the InputStream and pushes the data
        // to the Pipe.
        val pushThread = Thread(PushToImebraPipe(imebraPipe, stream))
        pushThread.start()

        val loadDataSet = CodecFactory.load(StreamReader(imebraPipe.streamInput))

        val dicomEntity = DicomEntity.convert(loadDataSet)

        framesCount = dicomEntity.numberOfFrames.toLong()

        tv_result.text = dicomEntity.toString()
        // Get the first frame from the dataset (after the proper modality transforms
        // have been applied).
        val dicomImage = loadDataSet.getImageApplyModalityTransform(index.toLong())

        // Use a DrawBitmap to build a stream of bytes that can be handled by the
        // Android Bitmap class.
        val chain = TransformsChain()
        if (ColorTransformsFactory.isMonochrome(dicomImage.colorSpace)) {
            val voilut = VOILUT(
                VOILUT.getOptimalVOI(
                    dicomImage,
                    0,
                    0,
                    dicomImage.width,
                    dicomImage.height
                )
            )
            chain.addTransform(voilut)
        }
        val drawBitmap = DrawBitmap(chain)
        val memory = drawBitmap.getBitmap(dicomImage, drawBitmapType_t.drawBitmapRGBA, 4)

        // Build the Android Bitmap from the raw bytes returned by DrawBitmap.
        val renderBitmap = Bitmap.createBitmap(
            dicomImage.width.toInt(), dicomImage.height.toInt(), Bitmap.Config.ARGB_8888
        )
        val memoryByte = ByteArray(memory.size().toInt())
        memory.data(memoryByte)
        val byteBuffer = ByteBuffer.wrap(memoryByte)
        renderBitmap.copyPixelsFromBuffer(byteBuffer)

        // Update the image
        iv.setImageBitmap(renderBitmap)
        iv.scaleType = ImageView.ScaleType.FIT_CENTER

        // Update the text with the patient name
        tv.text = loadDataSet.getPatientName(
            TagId(0x10, 0x10),
            index.toLong(),
            PatientName("Undefined", "", "")
        ).alphabeticRepresentation
    }

}