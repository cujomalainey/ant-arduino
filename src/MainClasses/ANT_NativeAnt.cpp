#include <MainClasses/ANT_NativeAnt.h>
#include <ANT_defines.h>

#ifdef NATIVE_API_AVAILABLE

NativeAnt::NativeAnt() {}

void NativeAnt::begin(){}

void NativeAnt::readPacket(){}

void NativeAnt::send(AntRequest &request){
    request.execute();
}

#endif // NATIVE_API_AVAILABLE