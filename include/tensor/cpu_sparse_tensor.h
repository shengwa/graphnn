#ifndef SPARSE_TENSOR_H
#define SPARSE_TENSOR_H

#include "tensor.h"
#include "t_data.h"

namespace gnn
{

/**
 * @brief      CPU SPARSE specialization of Tensor
 *
 * @tparam     Dtype  { float/double }
 */
template<typename Dtype>
class TensorTemplate<CPU, SPARSE, Dtype> : public Tensor
{
public:

	TensorTemplate();
	virtual ~TensorTemplate() {}
	virtual void Reshape(std::vector<size_t> l) override;
	virtual MatType GetMatType() override;
	virtual MatMode GetMatMode() override;
	
	void CopyFrom(SpTensor<CPU, Dtype>& src);
	void CopyFrom(SpTensor<GPU, Dtype>& src);
	
	/**
	 * @brief      shallow copy (only set the shared_ptr)
	 *
	 * @param      src   The source
	 */	
	void ShallowCopy(SpTensor<CPU, Dtype>& src);
	
	/**
	 * @brief      resize the sparse CSR structure
	 *
	 * @param[in]  newNNZ   new number of non-zeros
	 * @param[in]  newNPtr  new number of rows + 1
	 */
	void ResizeSp(int newNNZ, int newNPtr);

	/**
	 * @brief      find the max index along dimensions other than axis
	 *
	 * @param      dst   used to store the results
	 * @param[in]  axis  The axis to be kept
	 */
	void ArgMax(DTensor<CPU, int>& dst, uint axis = 0);

	/**
	 * the shared ptr to the data structure (which is used to keep the data of this tensor)
	 */
	std::shared_ptr< SparseData<CPU, Dtype> > data;
};

/**
 * @brief      CPU SPARSE int tensor specialization; this tensor is not used for heavy computation
 * 				(e.g., matmul)
 */
template<>
class TensorTemplate<CPU, SPARSE, int> : public Tensor
{
public:

	TensorTemplate();
	virtual ~TensorTemplate() {}
	virtual void Reshape(std::vector<size_t> l) override;
	virtual MatType GetMatType() override;
	virtual MatMode GetMatMode() override;
	/**
	 * @brief      shallow copy (only set the shared_ptr)
	 *
	 * @param      src   The source
	 */	
	void ShallowCopy(SpTensor<CPU, int>& src);
	/**
	 * @brief      resize the sparse CSR structure
	 *
	 * @param[in]  newNNZ   new number of non-zeros
	 * @param[in]  newNPtr  new number of rows + 1
	 */	
	void ResizeSp(int newNNZ, int newNPtr);
	/**
	 * the shared ptr to the data structure (which is used to keep the data of this tensor)
	 */	
	std::shared_ptr< SparseData<CPU, int> > data;
};

}

#endif