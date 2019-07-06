#include <occa/defines.hpp>
#include <occa/modes/cuda/registration.hpp>
#include <occa/modes/cuda/utils.hpp>

namespace occa {
  namespace cuda {
    modeInfo::modeInfo() {}

    bool modeInfo::init() {
#if OCCA_CUDA_ENABLED
      return cuda::init();
#else
      return false;
#endif
    }

    styling::section& modeInfo::getDescription() {
      static styling::section section("CUDA");
      if (section.size() == 0) {
        char deviceName[1024];
        int deviceCount = cuda::getDeviceCount();
        for (int i = 0; i < deviceCount; ++i) {
          const udim_t bytes         = getDeviceMemorySize(getDevice(i));
          const std::string bytesStr = stringifyBytes(bytes);

          OCCA_CUDA_ERROR("Getting Device Name",
                          cuDeviceGetName(deviceName, 1024, i));

          section
            .add("Device ID"  ,  toString(i))
            .add("Device Name",  deviceName)
            .add("Memory"     ,  bytesStr)
            .addDivider();
        }
        // Remove last divider
        section.groups.pop_back();
      }
      return section;
    }

    occa::mode<cuda::modeInfo,
               cuda::device> mode("CUDA");
  }
}
