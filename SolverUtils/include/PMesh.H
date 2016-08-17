/**
 \file 
 \ingroup support
 \brief Parallel Mesh Stuff

 All mesh data structures (MDS) will follow the CGNS conventions:\n
 \verbatim
 Triangle Edges: 12 23 31    (counterclockwise)
 Square Edges:   12 23 34 41 (ccw)
 Tet Faces:      132 241 342 143
 Pyr Faces:      1432 251 352 453 154
 Prism Faces:    2541 3652 1463 132 456
 Hex Faces:      1432 2651 3762 4873 1584 5678 
 \endverbatim 
 \image latex elements.eps "Element Types"
 \image html elements.jpg "Element Types" width=10cm
*/
/*
                  Supported Cell Types

        4                                              6   
       /|\             5       8---------7            /|\ 
      / | \         /  |       | \       |\          / | \
     /  |  \       /  /        |  \      | \        /  |  \
    /   |   \     /   |        |   5--------\6     /   3   \
   1----|----3   4----|-3      4---|-----3   |    4---------5
    \   |   /     \  /   \      \  |      \  |    |  /   \  |
     \  |  /       \ |    \      \ |       \ |    | /     \ |
      \ | /         \|     \      \|        \|    |/       \|
        2            1------2      1---------2    1---------2
 
*/
#ifndef _PMESH_H_
#define _PMESH_H_
#include "Mesh.H"
#include "COMM.H"

namespace SolverUtils { namespace Mesh {  
  /** 
      \brief Border data in CSR format
      \verbatim
   This is the border data in CSR format.  Review of CSR:
   Ap: is the array of sizes (in number of nonzero entries)
       in the Sparse Row.  Example: 
       [0 5 14 27 84 85 100] (5 in first row (row 0) in Ai[0:4]) 
                             (9 in row[1], Ai[5:13]), etc        
  
   Ai: is the array containing the column numbers of the nz 
       entries in the sparse row.  Example: 
       [0 3 4 7 8 1 5 ......] (row 0): X00XX00XX000.....
                              (row 1): 0X000X000000.....
  
   Ax: would store the actual values of the sparse matrix 
  
   Each row corresponds to a border *node* - so the actual send and
   receive arrays are puffed up to contain a number of matrix values
   required for nremote_dof * nlocal_dof.
     \endverbatim
  */
  struct BorderData {
    /// \brief sizes in ndof sent
    std::vector<Mesh::IndexType> SendAp; 
    /// \brief dof id's of the sent dofs
    std::vector<Mesh::IndexType> SendAi;
    /// \brief sizes in ndof recv
    std::vector<Mesh::IndexType> RecvAp;
    /// \brief dof id's of recvd dofs
    std::vector<Mesh::IndexType> RecvAi; 
    std::vector<Mesh::IndexType> border_dof_to_global;
    std::vector<double> SendBuffer;
    std::vector<double> RecvBuffer;
  };
  struct Border {
    Mesh::IndexType rpart;           /// remote partition id
    Mesh::IndexVec  nsend;           /// local id's of remote nodes
    Mesh::IndexVec  nrecv;           /// local id's of local nodes
    Mesh::IndexType recvsize;        /// total num owned dofs
    Mesh::IndexType sendsize;        /// hrm
    Mesh::IndexType remote_dofcount; /// total num remote dofs
    BorderData      data;            /// csr support/comm buffers
  };
  struct PartInfo {
    Mesh::IndexType npart;   /// total number of partitions
    Mesh::IndexType part;    /// partition id
    Mesh::IndexType nelem;   /// total number of elems
    Mesh::IndexType nnodes;  /// total number of nodes
    Mesh::IndexType nborder; /// number of borders
    Mesh::IndexType nshared; /// number of shared nodes
    Mesh::IndexType nown;    /// number of shared nodes owned
    Mesh::IndexType nlocal;  /// number of local nodes (convenience)
    Mesh::IndexType doffset; /// global dof offset
  };
  
  class Partition {
  private:
    IRAD::Comm::CommunicatorObject *_communicator;
  public:
    Partition() : _communicator(NULL), _mesh(),_info(),_borders() {};
    MeshUtilityObject _mesh;
    //    NodalCoordinates    _nc;
    //    Connectivity        _ec;
    PartInfo            _info;
    std::vector<Border> _borders;
    int Read(const std::string &meshname,int id);
//definition moved into header file for ease
    int Read(const std::string &MeshName,IRAD::Comm::CommunicatorObject &comm,
	     bool allow_n2m,std::ostream &ErrOut)
{
    unsigned int nproc = comm.Size();
    unsigned int rank = comm.Rank();
    unsigned int id = rank + 1;
    std::cout << "Partition::Read " << MeshName << "(" << nproc << "," << rank << "," << id << ")" << std::endl;
    // Read the partitioning info
    if(nproc > 1){
      std::ifstream InfoInf;
      std::ostringstream FNOstr;
      FNOstr << MeshName << "." << id << ".info";
      InfoInf.open(FNOstr.str().c_str());
      if(!InfoInf){
	comm.SetErr(1);
      }
      if(comm.Check()){
	ErrOut << "Partition::Read Could not find partition info for " << MeshName;
	return(1);
      }
      InfoInf >> _info.npart >> _info.part >> _info.nelem >> _info.nnodes >> _info.nborder 
	      >> _info.nshared >> _info.nown;
      std::cout << _info.npart << _info.part << _info.nelem << _info.nnodes << _info.nborder 
		<< _info.nshared << _info.nown;
      if(_info.npart != nproc && !allow_n2m){
	comm.SetErr(1);
      }
      if(comm.Check()){
	ErrOut << "Partition::Read " << MeshName << " has partition/processor mismatch: ("
	       << _info.npart << "/" << nproc << ").\n";
	return(1);
      }
      _info.nlocal = _info.nnodes  - _info.nshared + _info.nown;
      InfoInf.close();
    }
    else{
      _info.nborder = 0;
      _info.nshared = 0;
    }
    // done reading partition info
    std::ifstream Inf;
    std::ostringstream Ostr;
    Ostr << MeshName;
    if(nproc > 1)
      Ostr << "." << id << ".pmesh";
    else
      Ostr << ".mesh";
    Inf.open(Ostr.str().c_str());
    // Don't blink or you'll miss the mesh actually being loaded here.
    Inf >> _mesh.NC();
    Inf >> _mesh.ECon();
    _mesh.ECon().ShrinkWrap();
    //    Inf >> _nc >> _ec;
    //    _ec.ShrinkWrap();
    // done loading actual mesh  
    //    Mesh::IndexType number_of_nodes    = _nc.Size();
    //    Mesh::IndexType number_of_elements = _ec.Nelem();
    Mesh::IndexType number_of_nodes    = _mesh.NumberOfNodes();
    Mesh::IndexType number_of_elements = _mesh.NumberOfElements();
    if(nproc == 1){
      _info.nnodes = number_of_nodes;
      _info.nown   = 0;
      _info.nlocal = number_of_nodes;
      _info.nelem  = number_of_elements;
    }
    else{
      Inf >> _info.nborder;
      _borders.resize(_info.nborder);
      for(Mesh::IndexType nn = 0;nn < _info.nborder;nn++){
	Mesh::IndexType nrecv = 0;
	Mesh::IndexType nsend = 0;
	Inf >> _borders[nn].rpart >> nrecv >> nsend;
	_borders[nn].nrecv.resize(nrecv);
	for(Mesh::IndexType ii = 0;ii < nrecv;ii++){
	  Mesh::IndexType nodeid = 0;
	  Inf >> _borders[nn].nrecv[ii] >> nodeid;
	}
	_borders[nn].nsend.resize(nsend);
	for(Mesh::IndexType ii = 0;ii < nsend;ii++){
	  Mesh::IndexType nodeid = 0;
	  Inf >> _borders[nn].nsend[ii] >> nodeid;
	}
      }
    }
    Inf.close();
    _communicator = &comm;
    return(0);
  };

    //    IRAD::Comm::CommunicatorObject *CommunicatorPtr(){ return(_communicator); };
    //    std::ostream &Report(std::ostream &Ostr);
    MeshUtilityObject &Mesh() { return (_mesh); };
    const MeshUtilityObject &Mesh() const { return (_mesh); };
    PartInfo &Info() { return (_info); };
    const PartInfo &Info() const { return(_info); };
    std::vector<Border> &Borders() { return(_borders); };
    const std::vector<Border> &Borders() const { return(_borders); };
    IRAD::Comm::CommunicatorObject *CommunicatorPtr(){ return(_communicator); };
    //    std::ostream &Report(std::ostream &Ostr);
    int GetBorderElements(std::vector<Mesh::IndexType> &be) const;
  };
  
  } }
#endif
