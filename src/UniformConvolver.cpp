#include <assert.h>
#include <stdlib.h>
#include "./UniformConvolver.h"
#include "./ReverbAccumulationBuffer.h"
#include <omp.h>

UniformConvolver::UniformConvolver(double* impulseResponse, int impulseSize , int outputSize)
: m_accumulationBuffer(3*impulseSize, outputSize)
{
  m_outputSize = outputSize;
  m_impulseSize  = impulseSize;

  int n = m_impulseSize / m_outputSize;
  assert(m_impulseSize % m_outputSize == 0);

  for (int i = 0; i < n; i++) {
    m_fftFrames.push_back( new FFTFrame(impulseResponse, outputSize, &m_accumulationBuffer, i*m_outputSize));
  }
}

UniformConvolver::~UniformConvolver() {
  while(!m_fftFrames.empty()) {
    delete m_fftFrames.back();
    m_fftFrames.pop_back();
  }
}

void UniformConvolver::process(double *input, double *output) {

  omp_set_num_threads(12);
  #pragma omp parallel for
  for(int i = 0; i < m_fftFrames.size(); i++) {
    m_fftFrames[i]->process(input);
  }

  m_accumulationBuffer.loadOutput(output);
}

void UniformConvolver::print() {
  m_accumulationBuffer.print();
}


