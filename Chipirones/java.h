#pragma once
#include <jni.h>
#include <jvmti.h>
#include <mutex>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>

class lunar
{
public:
	JNIEnv* env;
	JavaVM* vm;

	void load_classes()
	{
		jvmtiEnv* jvmti;
		if (vm->GetEnv((void**) &jvmti, JVMTI_VERSION_1_2) != JNI_OK) return;

		jclass lang = env->FindClass("java/lang/Class");
		jmethodID method_id = env->GetMethodID(lang, "getName", "()Ljava/lang/String;");

		jclass* classes_ptr;
		jint amount;

		jvmti->GetLoadedClasses(&amount, &classes_ptr);
		for (int i = 0; i < amount; i++) {
			jstring name = (jstring)env->CallObjectMethod(classes_ptr[i], method_id);

			const char* className = env->GetStringUTFChars(name, 0);
			env->ReleaseStringUTFChars(name, className);

			classes.emplace(std::make_pair((std::string)className, classes_ptr[i]));

		}
	}

	jclass get_class(std::string class_name) {
		if (classes.contains(class_name)) return classes[class_name];

		return NULL;
	}

private:
	std::unordered_map<std::string, jclass> classes;
};

struct vec3d {
	double x, y, z;
};

inline auto lc = std::make_unique<lunar>();