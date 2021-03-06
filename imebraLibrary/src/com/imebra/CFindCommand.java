/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public class CFindCommand extends DimseCommand {
  private transient long swigCPtr;

  protected CFindCommand(long cPtr, boolean cMemoryOwn) {
    super(imebraJNI.CFindCommand_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(CFindCommand obj) {
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
        imebraJNI.delete_CFindCommand(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public CFindCommand(String abstractSyntax, int messageID, dimseCommandPriority_t priority, String affectedSopClassUid, DataSet identifier) {
    this(imebraJNI.new_CFindCommand__SWIG_0(abstractSyntax, messageID, priority.swigValue(), affectedSopClassUid, DataSet.getCPtr(identifier), identifier), true);
  }

  public CFindCommand(CFindCommand source) {
    this(imebraJNI.new_CFindCommand__SWIG_1(CFindCommand.getCPtr(source), source), true);
  }

}
