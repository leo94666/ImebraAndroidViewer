LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := imebra_lib
LOCAL_CPPFLAGS += -fexceptions -pthread -I$(LOCAL_PATH)/../../library/include
LOCAL_CPPFLAGS += -DIMEBRA_USE_JAVA -DIMEBRA_MEMORY_POOL_MAX_SIZE=4000000 -DIMEBRA_ANDROID -DIMEBRA_LOG_LEVEL_INFO
LOCAL_LDLIBS :=  -llog

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../library/src/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../library/implementation/*.cpp)
FILE_LIST += $(LOCAL_PATH)/../java_wrapper.cxx
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)
