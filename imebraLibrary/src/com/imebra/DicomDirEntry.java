/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class DicomDirEntry {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected DicomDirEntry(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(DicomDirEntry obj) {
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
        imebraJNI.delete_DicomDirEntry(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public DicomDirEntry(DicomDirEntry source) {
    this(imebraJNI.new_DicomDirEntry(DicomDirEntry.getCPtr(source), source), true);
  }

  public DataSet getEntryDataSet() {
    return new DataSet(imebraJNI.DicomDirEntry_getEntryDataSet(swigCPtr, this), true);
  }

  public boolean hasNextEntry() {
    return imebraJNI.DicomDirEntry_hasNextEntry(swigCPtr, this);
  }

  public DicomDirEntry getNextEntry() {
    return new DicomDirEntry(imebraJNI.DicomDirEntry_getNextEntry(swigCPtr, this), true);
  }

  public boolean hasChildren() {
    return imebraJNI.DicomDirEntry_hasChildren(swigCPtr, this);
  }

  public DicomDirEntry getFirstChildEntry() {
    return new DicomDirEntry(imebraJNI.DicomDirEntry_getFirstChildEntry(swigCPtr, this), true);
  }

  public StringsList getFileParts() {
    return new StringsList(imebraJNI.DicomDirEntry_getFileParts(swigCPtr, this), true);
  }

  public String getTypeString() {
    return imebraJNI.DicomDirEntry_getTypeString(swigCPtr, this);
  }

}
