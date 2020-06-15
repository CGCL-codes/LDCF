#include "LDCF.h"


using namespace std;


LogarithmicDynamicCuckooFilter::LogarithmicDynamicCuckooFilter(const size_t item_num, const double fp, const size_t exp_block_num){

	capacity = item_num;

	single_table_length = upperpower2(capacity/4.0/exp_block_num);
	single_capacity = single_table_length*0.9375*4;//s=6 1920 s=12 960 s=24 480 s=48 240 s=96 120

	false_positive = fp;
	single_false_positive = 1-pow(1.0-false_positive, ((double)single_capacity/capacity));

	fingerprint_size_double = ceil(log(8.0/single_false_positive)/log(2));
	counter = 0;


	curCF = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, 0);
	child0CF = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, 1);
	child1CF = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, 1);

	cf_tree = new LinkTree(single_table_length, fingerprint_size, single_capacity);
	cf_tree->cf_pt = curCF;
	cf_tree->child0_pt = child0CF;
	cf_tree->child1_pt = child1CF;
}

LogarithmicDynamicCuckooFilter::~LogarithmicDynamicCuckooFilter(){
	delete curCF;
	delete child0CF;
	delete child1CF
	delete cf_tree;
}



bool LogarithmicDynamicCuckooFilter::insertItem(const char* item){
	if(curCF->is_full == true){
		if(GetPre(item))
			curCF = getChild0CF(curCF);
		else
			curCF = getChild1CF(curCF);
	}

	if(curCF->insertItem(item, victim)){
		counter++;
	}else{
		counter++;
	}

	return true;
}

CuckooFilter* LogarithmicDynamicCuckooFilter::getChild0CF(CuckooFilter* curCF){
	if(curCF->child0CF == NULL){
		_child0CF = new CuckooFilter(single_table_length, fingerprint_size, single_capacity);
		curCF->child0CF = _child0CF;
		_child0CF->front = curCF;
		cf_list->child0_pt = _child0CF;
	}else{
		_child0CF = curCF->child0CF;
	}
	return _child0CF;
}

CuckooFilter* LogarithmicDynamicCuckooFilter::getChild0CF(CuckooFilter* curCF){
	if(curCF->child1CF == NULL){
		_child1CF = new CuckooFilter(single_table_length, fingerprint_size, single_capacity);
		curCF->child1CF = _child1CF;
		_child1CF->front = curCF;
		cf_list->child1_pt = _child1CF;
	}else{
		_child1CF = curCF->child1CF;
	}
	return _child1CF;
}

bool LogarithmicDynamicCuckooFilter::queryItem(const char* item){
	size_t index, alt_index;
	uint32_t fingerprint;

	generateIF(item, index, fingerprint, fingerprint_size, single_table_length, level);
	generateA(index, fingerprint, alt_index, single_table_length, level);

	CuckooFilter* query_pt = cf_tree->cf_pt;
	for(int count = 0; count<cf_tree->level; count++){

		if(query_pt->queryImpl(index, fingerprint)){
			return true;
		}else if(query_pt->queryImpl(alt_index, fingerprint)){
			return true;
		}else{
			if(GetPre(item)
				query_pt = query_pt->child0;
			else
				query_pt = query_pt->child1;
		}
		if(query_pt == 0){
			break;
		}

	}
	return false;
}

bool LogarithmicDynamicCuckooFilter::deleteItem(const char* item){
	size_t index, alt_index;
	uint32_t fingerprint;

	generateIF(item, index, fingerprint, fingerprint_size, single_table_length);
	generateA(index, fingerprint, alt_index, single_table_length);
	CuckooFilter* delete_pt = cf_tree->cf_pt;
	for(int count = 0; count<cf_tree->level; count++){
		if(delete_pt->queryImpl(index, fingerprint)){
			if(delete_pt->deleteImpl(index, fingerprint)){
				counter--;
				return true;
			}
		}else if(delete_pt->queryImpl(alt_index, fingerprint)){
			if(delete_pt->deleteImpl(alt_index ,fingerprint)){
				counter--;
				return true;
			}
		}else{
			if(GetPre(item)
				query_pt = query_pt->child0;
			else
				query_pt = query_pt->child1;
		}
	}
	return false;
}



void LogarithmicDynamicCuckooFilter::generateIF(const char* item, size_t &index, uint32_t &fingerprint, int fingerprint_size, int single_table_length, int level){
	std::string  value = HashFunc::sha1(item);
	uint64_t hv = *((uint64_t*) value.c_str());

	index = ((uint32_t) (hv >> 32)) % single_table_length;
	fingerprint = (uint32_t) (hv & 0xFFFFFFFF);
	fingerprint &= ((0x1ULL<<fingerprint_size)-1);
	fingerprint += (fingerprint == 0);
	fingerprint = fingerprint >> level;
}

void LogarithmicDynamicCuckooFilter::generateA(size_t index, uint32_t fingerprint, size_t &alt_index, int single_table_length, int level){
	alt_index = (index ^ (fingerprint * 0x5bd1e995)) % single_table_length;
}

bool LogarithmicDynamicCuckooFilter::GetPre(const char* item){
	std::string  value = HashFunc::sha1(item);
	uint64_t hv = *((uint64_t*) value.c_str());
	fingerprint = (uint32_t) (hv & 0xFFFFFFFF);
	if (fingerprint >> (fingerprint_size -1) ==0)
		return true;
	return false;
}



int LogarithmicDynamicCuckooFilter::getFingerprintSize(){
	return fingerprint_size;
}

float LogarithmicDynamicCuckooFilter::size_in_mb(){
	return fingerprint_size * 4.0 * single_table_length * cf_list->num / 8 / 1024 / 1024;
}

uint64_t LogarithmicDynamicCuckooFilter::upperpower2(uint64_t x) {
  x--;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x |= x >> 32;
  x++;
  return x;
}
