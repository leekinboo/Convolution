#ifndef FFTFrame_h
#define FFTFrame_h

#include "ReverbAccumulationBuffer.h"

class FFTFrame {
  public:
    FFTFrame(double *impulseResponse, int size, int readIndex);
    FFTFrame(double* impulseResponseChunk, int framesToProcess, ReverbAccumulationBuffer* accumulationBuffer, int index);
    int getReadIndex();
    void process(double* input);
    void print();

  private:
    double* m_impulseResponse;
    double* m_processBuffer;
    double* m_overflowBuffer;
    double* m_resultBuffer;
    int m_framesToProcess;
    int m_size;
    int m_readIndex;
    ReverbAccumulationBuffer* m_accumulationBuffer;
};
#endif
