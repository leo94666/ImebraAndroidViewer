/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class MutableMemory extends Memory {
  private transient long swigCPtr;

  protected MutableMemory(long cPtr, boolean cMemoryOwn) {
    super(imebraJNI.MutableMemory_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(MutableMemory obj) {
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
        imebraJNI.delete_MutableMemory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public MutableMemory() {
    this(imebraJNI.new_MutableMemory__SWIG_0(), true);
  }

  public MutableMemory(long initialSize) {
    this(imebraJNI.new_MutableMemory__SWIG_1(initialSize), true);
  }

  public MutableMemory(Memory sourceMemory) {
    this(imebraJNI.new_MutableMemory__SWIG_2(Memory.getCPtr(sourceMemory), sourceMemory), true);
  }

  public MutableMemory(MutableMemory source) {
    this(imebraJNI.new_MutableMemory__SWIG_3(MutableMemory.getCPtr(source), source), true);
  }

  public MutableMemory(byte[] source) {
    this(imebraJNI.new_MutableMemory__SWIG_4(source), true);
  }

  public void copyFrom(Memory sourceMemory) {
    imebraJNI.MutableMemory_copyFrom(swigCPtr, this, Memory.getCPtr(sourceMemory), sourceMemory);
  }

  public void clear() {
    imebraJNI.MutableMemory_clear(swigCPtr, this);
  }

  public void resize(long newSize) {
    imebraJNI.MutableMemory_resize(swigCPtr, this, newSize);
  }

  public void reserve(long reserveSize) {
    imebraJNI.MutableMemory_reserve(swigCPtr, this, reserveSize);
  }

  public void assign(byte[] source) {
    imebraJNI.MutableMemory_assign(swigCPtr, this, source);
  }

  public void assignRegion(byte[] source, long destinationOffset) {
    imebraJNI.MutableMemory_assignRegion(swigCPtr, this, source, destinationOffset);
  }

}
