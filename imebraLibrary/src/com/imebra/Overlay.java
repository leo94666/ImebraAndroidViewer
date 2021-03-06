/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class Overlay {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Overlay(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Overlay obj) {
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
        imebraJNI.delete_Overlay(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Overlay(Overlay source) {
    this(imebraJNI.new_Overlay(Overlay.getCPtr(source), source), true);
  }

  public long getFirstFrame() {
    return imebraJNI.Overlay_getFirstFrame(swigCPtr, this);
  }

  public long getFramesCount() {
    return imebraJNI.Overlay_getFramesCount(swigCPtr, this);
  }

  public int getZeroBasedOriginX() {
    return imebraJNI.Overlay_getZeroBasedOriginX(swigCPtr, this);
  }

  public int getZeroBasedOriginY() {
    return imebraJNI.Overlay_getZeroBasedOriginY(swigCPtr, this);
  }

  public int getOneBasedOriginX() {
    return imebraJNI.Overlay_getOneBasedOriginX(swigCPtr, this);
  }

  public int getOneBasedOriginY() {
    return imebraJNI.Overlay_getOneBasedOriginY(swigCPtr, this);
  }

  public overlayType_t getType() {
    return overlayType_t.swigToEnum(imebraJNI.Overlay_getType(swigCPtr, this));
  }

  public String getSubType() {
    return imebraJNI.Overlay_getSubType(swigCPtr, this);
  }

  public String getLabel() {
    return imebraJNI.Overlay_getLabel(swigCPtr, this);
  }

  public String getDescription() {
    return imebraJNI.Overlay_getDescription(swigCPtr, this);
  }

  public long getROIArea() {
    return imebraJNI.Overlay_getROIArea(swigCPtr, this);
  }

  public double getROIMean() {
    return imebraJNI.Overlay_getROIMean(swigCPtr, this);
  }

  public double getROIStandardDeviation() {
    return imebraJNI.Overlay_getROIStandardDeviation(swigCPtr, this);
  }

  public Image getImage(long frame) {
    return new Image(imebraJNI.Overlay_getImage(swigCPtr, this, frame), true);
  }

}
