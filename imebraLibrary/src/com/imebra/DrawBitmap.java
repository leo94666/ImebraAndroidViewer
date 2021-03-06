/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class DrawBitmap {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected DrawBitmap(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(DrawBitmap obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        imebraJNI.delete_DrawBitmap(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public DrawBitmap() {
    this(imebraJNI.new_DrawBitmap__SWIG_0(), true);
  }

  public DrawBitmap(Transform transformsChain) {
    this(imebraJNI.new_DrawBitmap__SWIG_1(Transform.getCPtr(transformsChain), transformsChain), true);
  }

  public DrawBitmap(DrawBitmap source) {
    this(imebraJNI.new_DrawBitmap__SWIG_2(DrawBitmap.getCPtr(source), source), true);
  }

  public long getBitmap(Image image, drawBitmapType_t drawBitmapType, long rowAlignBytes, byte[] destination) {
    return imebraJNI.DrawBitmap_getBitmap__SWIG_0(swigCPtr, this, Image.getCPtr(image), image, drawBitmapType.swigValue(), rowAlignBytes, destination);
  }

  public Memory getBitmap(Image image, drawBitmapType_t drawBitmapType, long rowAlignBytes) {
    return new Memory(imebraJNI.DrawBitmap_getBitmap__SWIG_1(swigCPtr, this, Image.getCPtr(image), image, drawBitmapType.swigValue(), rowAlignBytes), true);
  }

}
