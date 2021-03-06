/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class VOIs extends java.util.AbstractList<VOIDescription> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected VOIs(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(VOIs obj) {
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
        imebraJNI.delete_VOIs(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public VOIs(VOIDescription[] initialElements) {
    this();
    reserve(initialElements.length);

    for (VOIDescription element : initialElements) {
      add(element);
    }
  }

  public VOIs(Iterable<VOIDescription> initialElements) {
    this();
    for (VOIDescription element : initialElements) {
      add(element);
    }
  }

  public VOIDescription get(int index) {
    return doGet(index);
  }

  public VOIDescription set(int index, VOIDescription e) {
    return doSet(index, e);
  }

  public boolean add(VOIDescription e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, VOIDescription e) {
    modCount++;
    doAdd(index, e);
  }

  public VOIDescription remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public VOIs() {
    this(imebraJNI.new_VOIs__SWIG_0(), true);
  }

  public VOIs(VOIs other) {
    this(imebraJNI.new_VOIs__SWIG_1(VOIs.getCPtr(other), other), true);
  }

  public long capacity() {
    return imebraJNI.VOIs_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    imebraJNI.VOIs_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return imebraJNI.VOIs_isEmpty(swigCPtr, this);
  }

  public void clear() {
    imebraJNI.VOIs_clear(swigCPtr, this);
  }

  public VOIs(int count, VOIDescription value) {
    this(imebraJNI.new_VOIs__SWIG_2(count, VOIDescription.getCPtr(value), value), true);
  }

  private int doSize() {
    return imebraJNI.VOIs_doSize(swigCPtr, this);
  }

  private void doAdd(VOIDescription x) {
    imebraJNI.VOIs_doAdd__SWIG_0(swigCPtr, this, VOIDescription.getCPtr(x), x);
  }

  private void doAdd(int index, VOIDescription x) {
    imebraJNI.VOIs_doAdd__SWIG_1(swigCPtr, this, index, VOIDescription.getCPtr(x), x);
  }

  private VOIDescription doRemove(int index) {
    return new VOIDescription(imebraJNI.VOIs_doRemove(swigCPtr, this, index), true);
  }

  private VOIDescription doGet(int index) {
    return new VOIDescription(imebraJNI.VOIs_doGet(swigCPtr, this, index), false);
  }

  private VOIDescription doSet(int index, VOIDescription val) {
    return new VOIDescription(imebraJNI.VOIs_doSet(swigCPtr, this, index, VOIDescription.getCPtr(val), val), true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    imebraJNI.VOIs_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}
