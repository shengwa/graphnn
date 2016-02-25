#ifndef C_MUL_LAYER_H
#define C_MUL_LAYER_H

#include "ilayer.h"

template<MatMode mode, typename Dtype>
class CMulLayer : public ILayer<mode, Dtype>
{
public:
    CMulLayer(NNGraph<mode, Dtype>* _nn, PropErr _properr = PropErr::T)
        : ILayer<mode, Dtype>(_nn, _properr) 
    {
        this->state = new DenseMat<mode, Dtype>();
		this->grad = new DenseMat<mode, Dtype>();
    }
    
    virtual void UpdateOutput(std::vector< ILayer<mode, Dtype>* >& operands) override
    {
        
    }
};

#endif