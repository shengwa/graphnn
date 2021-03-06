#include "nn/param_set.h"
#include <cassert>

namespace gnn
{

template<typename mode, typename Dtype>
ParamSet<mode, Dtype>::ParamSet()
{
	params.clear();
}

template<typename mode, typename Dtype>
void ParamSet<mode, Dtype>::AddParam(std::shared_ptr< DTensorVar<mode, Dtype> > param)
{
	ASSERT(params.count(param->name) == 0, "param " + param->name + " already created");
	params[param->name] = param;
}

template<typename mode, typename Dtype>
void ParamSet<mode, Dtype>::Save(std::string filename)
{
	FILE* fid = fopen(filename.c_str(), "wb");	
	ASSERT(fid, "file " + filename + " is not found");
	for (auto& p : params)
	{
		p.second->Serialize(fid);
	}

	fclose(fid);
}

template<typename mode, typename Dtype>
void ParamSet<mode, Dtype>::Load(std::string filename)
{
	FILE* fid = fopen(filename.c_str(), "rb");
	ASSERT(fid, "file " + filename + " is not found");
	for (auto& p : params)
		p.second->Deserialize(fid);

	fclose(fid);
}

template<typename mode, typename Dtype>
void ParamSet<mode, Dtype>::DeepCopyFrom(ParamSet<mode, Dtype>& src)
{
	for (auto& p : src.params)
	{
		if (params.count(p.first) == 0)
			params[p.first] = std::make_shared< DTensorVar<mode, Dtype> >(p.first);
		params[p.first]->value.CopyFrom(p.second->value);
	}
}

template class ParamSet<CPU, float>;
template class ParamSet<CPU, double>;
template class ParamSet<GPU, float>;
template class ParamSet<GPU, double>;


}