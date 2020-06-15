#ifndef LINKTREE_H_
#define LINKTREE_H_

class LinkTree{
public:
	CuckooFilter* cf_pt;
	CuckooFilter* child0_pt;
	CuckooFilter* child1_pt;
	int num;
	int level;
	LinkTree(size_t single_table_length, size_t fingerprint_size, double single_capacity, curlevel){
		cf_pt = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, curlevel);
		child0_pt = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, curlevel+1);
		child1_pt = new CuckooFilter(single_table_length, fingerprint_size, single_capacity, curlevel+1);
		num = 0;
		level = curlevel;
	}
	~LinkTree(){
		delete cf_pt;
		cf_pt = NULL;
		delete child0_pt;
		tail_pt = NULL;
		delete child1_pt;
		tail_pt = NULL;
	}
	bool release(CuckooFilter* cf_release){
		CuckooFilter* emptyCF = new (0, 0, 0, curlevel);
		CuckooFilter* frontCF = cf_release->front;
		if(frontCF == NULL){
			this->cf_pt = emptyCF;
		}else if (frontCF->_0_child == cf_release){{
			frontCF->_0_child = emptyCF;
		}else{
			frontCF->_1_child = emptyCF;
		}
		emptyCF->_0_child = cf_relase->_0_child;
		emptyCF->_1_child = cf_relase->_1_child;
		cf_release = NULL;
		return true;
	}
};



#endif /* LINKTREE_H_ */
