#ifndef MYTHNVDECINTEROP_H
#define MYTHNVDECINTEROP_H

// MythTV
#include "opengl/mythopenglinterop.h"

// FFmpeg
extern "C" {
#include "compat/cuda/dynlink_loader.h"
#include "libavutil/hwcontext_cuda.h"
}

class MythNVDECInterop : public MythOpenGLInterop
{
    friend class MythOpenGLInterop;

  public:
    static MythNVDECInterop* Create(MythRenderOpenGL* Context);
    static bool CreateCUDAContext(MythRenderOpenGL* GLContext, CudaFunctions*& CudaFuncs,
                                  CUcontext& CudaContext);
    static void CleanupContext(MythRenderOpenGL* GLContext, CudaFunctions*& CudaFuncs,
                               CUcontext& CudaContext);

    bool IsValid();
    CUcontext GetCUDAContext();
    vector<MythVideoTextureOpenGL*> Acquire(MythRenderOpenGL* Context, MythVideoColourSpace* ColourSpace,
                                            MythVideoFrame* Frame, FrameScanType Scan) override;

  protected:
    static Type GetInteropType(VideoFrameType Format);
    explicit MythNVDECInterop(MythRenderOpenGL* Context);
   ~MythNVDECInterop() override;

  private:
    bool           InitialiseCuda();
    void           DeleteTextures() override;
    void           RotateReferenceFrames(CUdeviceptr Buffer);
    static bool    CreateCUDAPriv(MythRenderOpenGL* GLContext, CudaFunctions*& CudaFuncs,
                                  CUcontext& CudaContext, bool& Retry);
    CUcontext      m_cudaContext;
    CudaFunctions* m_cudaFuncs { nullptr };
    QVector<CUdeviceptr> m_referenceFrames;
};

#endif
