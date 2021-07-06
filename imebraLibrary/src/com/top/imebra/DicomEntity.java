package com.top.imebra;

import com.imebra.Age;
import com.imebra.DataSet;
import com.imebra.PatientName;
import com.imebra.TagId;

public class DicomEntity {
    private String PatientsId;
    private String PatientsName;
    private String PatientsBirthDate;
    private int NumberOfFrames;


    public DicomEntity() {

    }

    public DicomEntity(String patientsId, String patientsName, int numberOfFrames) {
        PatientsId = patientsId;
        PatientsName = patientsName;
        NumberOfFrames = numberOfFrames;
    }


    public String getPatientsId() {
        return PatientsId;
    }

    public void setPatientsId(String patientsId) {
        PatientsId = patientsId;
    }

    public String getPatientsName() {
        return PatientsName;
    }

    public String getPatientsBirthDate() {
        return PatientsBirthDate;
    }

    public void setPatientsBirthDate(String patientsBirthDate) {
        PatientsBirthDate = patientsBirthDate;
    }

    public void setPatientsName(String patientsName) {
        PatientsName = patientsName;
    }

    public int getNumberOfFrames() {
        return NumberOfFrames;
    }

    public void setNumberOfFrames(int numberOfFrames) {
        NumberOfFrames = numberOfFrames;
    }

    @Override
    public String toString() {
        return "DicomEntity{" +
                "PatientsId='" + PatientsId + '\'' +
                ", PatientsName='" + PatientsName + '\'' +
                ", PatientsBirthDate='" + PatientsBirthDate + '\'' +
                ", NumberOfFrames=" + NumberOfFrames +
                '}';
    }

    public static DicomEntity convert(DataSet dataSet) {
        DicomEntity dicomEntity = new DicomEntity();

        try {
            PatientName patientName = dataSet.getPatientName(new TagId(0x0010, 0x0010), 0);
            dicomEntity.setPatientsName(patientName.getAlphabeticRepresentation());

        } catch (Exception e) {
            dicomEntity.setPatientsName("null");
        }

        try {
            Age age = dataSet.getAge(new TagId(0x0010, 0x0010), 0);



        } catch (Exception e) {
            dicomEntity.setPatientsBirthDate("null");
        }

        try {
            long frameCounts = dataSet.getUint32(new TagId(0x0028, 0x0008), 0);
            dicomEntity.setNumberOfFrames((int) frameCounts);
        } catch (Exception e) {
            dicomEntity.setNumberOfFrames(1);
        }
        return dicomEntity;
    }
}
