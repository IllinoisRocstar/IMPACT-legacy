/**
 \file
 \ingroup support
 \brief Mesh Stuff
 \author MTC

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
#ifndef __Mesh_H__
#define __Mesh_H__
#include <set>
#include <limits>
#include <cstring>

#include "GeoPrimitives.H"
#include "primitive_utilities.H"

/**
   \namespace Mesh
   \ingroup support
   \brief Everything mesh

   The Mesh namespace encapsulates all the mesh-related data structures
   and algorithms that operate on them.

 */

namespace SolverUtils { 
  namespace Mesh {

    const double TOL = GeoPrim::TOL;
    const double LTOL = 0.0 - TOL;
    const double HTOL = 1.0 + TOL;

    typedef IRAD::Primitive::IndexType IndexType;
    typedef IRAD::Primitive::ubyte CellEntityIDType;
    typedef std::pair<Mesh::IndexType,CellEntityIDType> SubEntityId;
    typedef std::pair<SubEntityId,SubEntityId> SymbolicFace;
    typedef std::vector<Mesh::IndexType> IndexVec;
    typedef IRAD::Primitive::MultiContainer<Mesh::IndexType>::VecVec MultiVec;
    typedef IRAD::Primitive::MultiContainer<Mesh::IndexType,Mesh::IndexType>::VecMap VecMap;
    typedef IRAD::Primitive::ubyte GeoDimType;
    typedef std::string GeoNameType;

    template<typename OuterCont,typename OutCont,typename InnerCont,typename MapType>
    void MapElements(OuterCont &src,OutCont &trg,MapType &m)
    {
      trg.resize(src.size());
      typename OuterCont::iterator sci = src.begin();
      typename OutCont::iterator oci = trg.begin();
      while(sci != src.end()){
        typename InnerCont::iterator ici = sci->begin();
        while(ici != sci->end())
          oci->push_back(m[*ici++]);
        sci++;
        oci++;
      }
    };

    /// Return the maximum of all elements of a multicontainer
    template<typename ListContainerType, typename ListType>
    Mesh::IndexType MaxNodeId(const ListContainerType &fc)
    {
      Mesh::IndexType maxid = 0;
      typename ListContainerType::const_iterator lci = fc.begin();
      while(lci != fc.end()){
        typename ListType::const_iterator li = lci->begin();
        while(li != lci->end()){
          if(maxid < *li)
            maxid = *li;
          li++;
        }
      }
      return(maxid);
    };

    /// Populate OutCont with a flat list of entries from a multicontainer
    //  template<typename OuterCont,typename InnerCont,typename OutCont>
    //  void Flatten(OuterCont &con,OutCont &ocon){
    //    typename OuterCont::iterator cci = con.begin();
    //    ocon.resize(0);
    //    while(cci != con.end()){
    //      typename InnerCont::iterator ccni = cci->begin();
    //      while(ccni != cci->end())
    //	ocon.push_back(*ccni++);
    //      cci++;
    //    }
    //  };

    /// Return the total number of entries in a multicontainer
    //  template<typename OuterContType>
    //  Mesh::IndexType GetTotalSize(OuterContType &con)
    //  {
    //    Mesh::IndexType total_size = 0;
    //    typename OuterContType::iterator ci = con.begin();
    //    while(ci != con.end()){
    //      total_size += ci->size();
    //      ci++;
    //    }
    //    return(total_size);
    //  };


    template<typename OuterContType,typename InnerContType,typename RetCont,typename idxtype>
    void Container2CSR(RetCont &xadj,RetCont &adj,
                       OuterContType &source)
    {
      Mesh::IndexType number_of_elements = source.size();
      xadj.resize(number_of_elements+1);
      Mesh::IndexType number_entries = IRAD::Util::GetTotalSize<OuterContType>(source);
      adj.reserve(number_entries);
      typename OuterContType::iterator si = source.begin();
      Mesh::IndexType elm = 0;
      xadj[elm++] = 0;
      while(si != source.end()){
        typename InnerContType::iterator ei = si->begin();
        xadj[elm] = static_cast<idxtype>(si->size() + xadj[elm-1]);
        elm++;
        while(ei != si->end())
          adj.push_back(static_cast<idxtype>(*ei++-1));
        si++;
      }
    };


    /// Given an array of adjacent node lists (like an array
    /// of face connectivities), this function will loop thru
    /// and create a list of unique adjacent nodes for each node
    /// with the nodes that *are actually adjacent in the lists*
    template<typename ListContainerType, typename ListType>
    void CreateAdjacentNodeList(std::vector<std::list<Mesh::IndexType> > &anodelist,
                                ListContainerType &fc,Mesh::IndexType nnodes=0)
    {
      if(nnodes == 0)
        nnodes = MaxNodeId<ListContainerType,ListType>(fc);
      anodelist.resize(nnodes);
      typename ListContainerType::iterator lci = fc.begin();
      while(lci != fc.end())
        {
          typename ListType::iterator li = lci->begin();
          while(li != lci->end()){
            Mesh::IndexType this_node = *li++ - 1;
            Mesh::IndexType next_node = 0;
            if(li == lci->end())
              next_node = *(lci->begin());
            else
              next_node = *li++;
            anodelist[this_node].push_back(next_node);
            anodelist[next_node-1].push_back(this_node+1);
          }
          lci++;
        }
      for(Mesh::IndexType node = 0;node < nnodes;node++)
        {
          anodelist[node].sort();
          anodelist[node].unique();
        }
    }

    /// Given an array of adjacent node lists (like an array
    /// of face connectivities), this function will loop thru
    /// and create a list of unique adjacent nodes for each node
    /// Note that this is a little different from the AdjNodeList
    /// because in this version *every node in each list* is considered
    /// adjacent.
    template<typename ListContainerType, typename ListType>
    void AdjEList(std::vector<std::list<Mesh::IndexType> > &aelist,
                  ListContainerType &dual_con,unsigned long nel=0)
    {
      if(nel == 0)
        nel = MaxNodeId<ListContainerType,ListType>(dual_con);
      aelist.resize(nel);
      typename ListContainerType::iterator lci = dual_con.begin();
      while(lci != dual_con.end())
        {
          typename ListType::iterator li = lci->begin();
          while(li != lci->end()){
            Mesh::IndexType this_node = *li++ - 1;
            typename ListType::iterator li2 = li;
            while(li2 != lci->end()){
              Mesh::IndexType nexnode = *li2++ - 1;
              aelist[this_node].push_back(nexnode+1);
              aelist[nexnode].push_back(this_node+1);
            }
          }
          lci++;
        }
      for(Mesh::IndexType node = 0;node < nel;node++)
        {
          aelist[node].sort();
          aelist[node].unique();
        }
    }

    // Requires a certain format for the input.   The con must
    // be a sorted list of unique adjacent nodes.
    template<typename ConType,typename IConType>
    Mesh::IndexType NumberOfEdges(ConType &con)
    {
      typename ConType::iterator ci = con.begin();
      Mesh::IndexType node = 0;
      Mesh::IndexType nedges = 0;
      while(ci != con.end())
        {
          Mesh::IndexType tnode = ++node;
          typename IConType::iterator eni = ci->begin();
          while(eni != ci->end())
            {
              Mesh::IndexType anode = *eni++;
              if((tnode) < anode)
                nedges++;
            }
          ci++;
        }
      return(nedges);
    }

    template<typename ContainerType,typename Icont>
    void FormGraph(const ContainerType &adjlist)
    {
      // empty for now
    };

    class TestFace : public std::list<Mesh::IndexType>
    {
    public:
      bool operator<(const TestFace &f);
    };

    class NodalCoordinates {
      friend std::ostream &operator<<(std::ostream &oSt,
                                      const Mesh::NodalCoordinates &nc);
      friend std::istream &operator>>(std::istream &iSt,
                                      Mesh::NodalCoordinates &nc);
    private:
      bool mydata;
      int verblevel;
      std::ostream *Out;
      std::ostream *Err;
    protected:
      double *ncdata;
      Mesh::IndexType nnodes;
    public:
      NodalCoordinates();
      NodalCoordinates(Mesh::IndexType n);
      NodalCoordinates(Mesh::IndexType n,double *data);

      // Currently, these two constructors *copy* data - eventually, would
      // like to add transparent support for strided and blocked data
      NodalCoordinates(Mesh::IndexType n,double *data,int stride);
      NodalCoordinates(Mesh::IndexType n,double *xdata,double *ydata,double *zdata);

      ~NodalCoordinates();
      bool good() const;
      Mesh::IndexType size() const;
      Mesh::IndexType Size() const;
      double *Data(){return(ncdata);};
      void destroy();
      void init();
      void init(Mesh::IndexType n);
      void init(Mesh::IndexType n, double *data);
      void init_node(Mesh::IndexType n, const GeoPrim::CPoint &);
      void init_copy(Mesh::IndexType n, double *data);
      void init_copy(Mesh::IndexType n, double *data,int stride);
      void init_copy(Mesh::IndexType n, double *xdata,double *ydata,double *zdata);
      void cleanup(double tol);
      inline int NNodes( ) const { return nnodes; };

      inline double &x(Mesh::IndexType n = 1)
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(n-1)*3]);
      };
      inline const double &x(Mesh::IndexType n = 1) const
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(n-1)*3]);
      };
      inline double &y(Mesh::IndexType n = 1)
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(3*(n-1))+1]);
      };
      inline const double &y(Mesh::IndexType n = 1) const
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(3*(n-1))+1]);
      };
      inline double &z(Mesh::IndexType n = 1)
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(3*(n-1))+2]);
      };
      inline const double &z(Mesh::IndexType n = 1) const
      {
        assert(!(n > nnodes || n == 0));
        return(ncdata[(3*(n-1))+2]);
      };
      inline double *operator[](Mesh::IndexType n)
      {
        assert(!(n > nnodes || n == 0));
        return(&ncdata[3*(n-1)]);
      };
      inline const double *operator[](Mesh::IndexType n) const
      {
        assert(!(n > nnodes || n == 0));
        return(&ncdata[3*(n-1)]);
      };
      const GeoPrim::CPoint closest_point(const GeoPrim::CPoint &p) const;
      Mesh::IndexType closest_node(const GeoPrim::CPoint &p,double *dist_ptr = NULL) const;
    };


    class NeighborHood : public std::vector<std::set<Mesh::IndexType> >
    {};

    void DisplaceNodalCoordinates(Mesh::NodalCoordinates &nc,std::vector<double> &displacements);

    ///
    /// \brief General connectivity object
    ///
    /// The Connectivity is a very useful object which allows the
    /// description of adjacency of many types of things.  Currently
    /// the most obvious is describing the connectivity of mesh cells.
    ///
    class Connectivity : public std::vector<std::vector<Mesh::IndexType> >
    {
      friend std::ostream &operator<<(std::ostream &oSt,const Connectivity &ec);
      friend std::istream &operator>>(std::istream &iSt,Connectivity &ec);
    private:
      Mesh::IndexType _nelem;
      std::vector<Mesh::IndexType> _sizes;
    public:
      Connectivity();
      Connectivity(unsigned int N);
      void Resize(unsigned int N = 0);
      ~Connectivity();
      inline std::vector<Mesh::IndexType> &Element(Mesh::IndexType n){
        assert(n > 0 && n <= _nelem);
        return((*this)[n-1]);
      };
      inline std::vector<Mesh::IndexType> Element(Mesh::IndexType n) const {
        assert(n > 0 && n <= _nelem);
        return((*this)[n-1]);
      };
      inline Mesh::IndexType &Node(Mesh::IndexType e,Mesh::IndexType n){
        assert(e > 0 && e <= _nelem && n > 0);
        assert(n <= (*this)[e-1].size());
        return((*this)[e-1][n-1]);
      };
      inline Mesh::IndexType Node(Mesh::IndexType e,Mesh::IndexType n) const {
        assert(e > 0 && e <= _nelem && n > 0);
        assert(n <= (*this)[e-1].size());
        return((*this)[e-1][n-1]);
      };
      inline Mesh::IndexType Nelem() const { return _nelem;};
      inline Mesh::IndexType Esize(Mesh::IndexType n) const
      {
        assert(n > 0 && n <= _nelem);
        return (_sizes.empty() ? (*this)[n-1].size() : _sizes[n-1]);
      };
      void AddElement(const std::vector<Mesh::IndexType> &elem);
      void AddElements(Mesh::IndexType nielem,Mesh::IndexType nnpe,const std::vector<Mesh::IndexType> &elem);
      void AddElement();
      void AddElement(Mesh::IndexType a,Mesh::IndexType b,Mesh::IndexType c);
      void AddElement(Mesh::IndexType a,Mesh::IndexType b,Mesh::IndexType c,Mesh::IndexType d);
      void AddElement(Mesh::IndexType a,Mesh::IndexType b,Mesh::IndexType c,Mesh::IndexType d,
                      Mesh::IndexType e);
      void AddElement(Mesh::IndexType a,Mesh::IndexType b,Mesh::IndexType c,Mesh::IndexType d,
                      Mesh::IndexType e,Mesh::IndexType f);
      void AddElement(Mesh::IndexType a,Mesh::IndexType b,Mesh::IndexType c,Mesh::IndexType d,
                      Mesh::IndexType e,Mesh::IndexType f,Mesh::IndexType g,Mesh::IndexType h);
      void Sync();
      void ShrinkWrap();
      void Truncate();
      void destroy();
      void SyncSizes();
      void DestroySizes();
      void Inverse(Connectivity &,Mesh::IndexType nnodes=0) const;
      void InverseDegenerate(Connectivity &,Mesh::IndexType nnodes=0) const;
      void GetNeighborhood(NeighborHood &,const Connectivity &dc);
      void GetNeighborhood(Connectivity &,Connectivity &dc,
                           bool exclude_self=true,
                           bool sortit=false);
      void GetAdjacent(Connectivity &rl,
                       Connectivity &dc,
                       Mesh::IndexType n = 0,
                       bool sortit=false);
      void graph_mode(Mesh::IndexType offset = 0);
      void matrix_mode(Mesh::IndexType offset = 0);
      void BuildFaceConnectivity(Connectivity &fcon,Connectivity &ef,
                                 std::vector<Mesh::SymbolicFace> &sf,Connectivity &dc) const;
      template<typename T>
      void Flatten(std::vector<T> &outcon) const
      {
        outcon.resize(0);
        std::vector<std::vector<Mesh::IndexType> >::const_iterator eci = this->begin();
        while(eci != this->end()){
          std::vector<Mesh::IndexType>::const_iterator eni = eci->begin();
          while(eni != eci->end())
            outcon.push_back(*eni++);
          eci++;
        }
      };
      void BreadthFirstRenumber(std::vector<Mesh::IndexType> &remap);
      void ElementsOn(std::vector<Mesh::IndexType> &nodes,
                      Connectivity &dc,
                      std::vector<Mesh::IndexType> &subset);

    };


    ///
    /// \brief Connects continuous to discrete
    ///
    /// The GeometricEntity object encodes a physical geometry
    /// by dimension and can maintain a list of all discrete
    /// mesh entities that are associated with the given
    /// geometrical object.\n
    /// Here is a brief description of the types of objects
    /// we can represent with a GeometricEntity and their
    /// interconnections:\n
    /** \verbatim
        dim  discrete   physical
        ---  --------   --------
        0     Node       Point
        1     Edge       Curve
        2     Face      Surface
        3    Region      Volume
        \endverbatim */
    // Could code the index and dimension info into a single byte.
    // (Assuming we'd never have more than 64 distinct constructs)
    class GeometricEntity : public std::pair<GeoNameType,GeoDimType>
    {
      friend std::ostream &operator<<(std::ostream &oSt,
                                      const Mesh::GeometricEntity &ge);
      friend std::istream &operator>>(std::istream &iSt,
                                      Mesh::GeometricEntity &ge);
    public:
      GeoNameType Name() const { return this->first;  };
      GeoDimType  Dim()  const { return this->second; };
      // The Connectivity has size = Dim()+1, and specifies
      // the mesh entities associated with this geometrical
      // entity.
      Mesh::Connectivity _collections;
    };

    struct UnstructuredMesh {
      NodalCoordinates nc;
      Connectivity con;
    };

    int Skin(Mesh::UnstructuredMesh &inmesh,Mesh::UnstructuredMesh &outmesh);
    int WriteVTKToStream(Mesh::UnstructuredMesh &mesh,std::ostream &Ostr);
    int WriteVTKToStream(const std::string &name,Mesh::UnstructuredMesh &mesh,std::ostream &Ostr);
    int ReadWRLFromStream(Mesh::UnstructuredMesh &mesh,std::istream &Istr);


    class MeshUtilityObject {
    public:
      enum MeshConType { EN=0,ENDUAL,ED,EDDUAL,EF,EFDUAL,DN,DNDUAL,DF,DFDUAL,FN, FNDUAL ,NCONS};
    protected:
      NodalCoordinates _nodal_coordinates;
      std::vector<Connectivity> _connectivities;
    public:
      MeshUtilityObject() : _nodal_coordinates()
      {
        //      std::cout << "Mesh utility constructor" << std::endl;
        //      _nodal_coordinates_ptr = new NodalCoordinates();
        _connectivities.resize(NCONS);
        //      _connectivities[EN] = new Connectivity();
      };
      int NumberOfNodes() const { return(_nodal_coordinates.Size()); };
      int NumberOfElements() const { return(_connectivities[EN].Nelem()); };
      NodalCoordinates &NC()
      {
        return(_nodal_coordinates);
      };
      const NodalCoordinates &NC() const 
      {
        return(_nodal_coordinates);
      };
      Connectivity &ECon()
      {
        return(_connectivities[EN]);
      };
      const Connectivity &ECon() const
      {
        return(_connectivities[EN]);
      };
      Connectivity &Con(const MeshConType type)
      {
        //      if(!_connectivities[type])
        //	FormConnectivity(type);
        return(_connectivities[type]);
      };
      const Connectivity &Con(const MeshConType type) const
      {
        //      if(!_connectivities[type])
        //	(const_cast<MeshUtilityObject*>(this))->FormConnectivity(type);
        return(_connectivities[type]);

      };
      Connectivity &GetCon(const MeshConType type)
      {
        if(_connectivities[type].empty())
          FormConnectivity(type);
        return(_connectivities[type]);
      };
      const Connectivity &GetCon(const MeshConType type) const
      {
        if(_connectivities[type].empty())
          (const_cast<MeshUtilityObject*>(this))->FormConnectivity(type);
        return(_connectivities[type]);

      };
      int FormConnectivity(const MeshConType type)
      {
        switch(type) 
          {
          case ENDUAL:
            //	  if(_connectivities[type]){
            //	    _connectivities[type]->destroy();
            //	  }
            //	  else
            //	    _connectivities[type] = new Connectivity();
            ECon().Inverse(_connectivities[type],NC().Size());
            break;
          default:
            bool connectivity_known_type = false;
            assert(connectivity_known_type);
            break;
          }
        return(0);
      };
      int DestroyConnectivity(const MeshConType type)
      {
        //      if(_connectivities[type]){
        _connectivities[type].destroy();
        //	delete _connectivities[type];
        //	_connectivities[type] = NULL;
        //      }
        return(0);
      };
      ~MeshUtilityObject()
      {
        //      std::cout << "destroying mesh util" << std::endl;
        _nodal_coordinates.destroy();
        //      delete _nodal_coordinates_ptr;
        std::vector<Connectivity>::iterator cpi = _connectivities.begin();
        while(cpi != _connectivities.end())
          cpi++->destroy();
      };
    };

    int ReadMesh(const std::string &path,Mesh::UnstructuredMesh &mesh);

    int ReadMeshFromStream(Mesh::UnstructuredMesh &mesh,std::istream &Inf);

    // Class to encapsulate all the element specific methods
    // Should be renamed to generic cell
    class GenericCell_2 {
    protected:
      Mesh::IndexType _size; // Number of nodes
    public:
      GenericCell_2(Mesh::IndexType s = 3): _size(s){};
      void init(Mesh::IndexType s = 3){_size = s;};
      Mesh::IndexType size() const {return(_size);};
      GeoPrim::C3Point Centroid();
      Mesh::IndexType nedges() const {return(_size);};
      Mesh::IndexType nvert() const {return(_size);};
      void ReOrient(std::vector<Mesh::IndexType> &ec);
      double Area(Mesh::IndexType elnum,
                  const Connectivity &ec,
                  const NodalCoordinates &nc);
      //    bool Inverted(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc,
      //                  const GeoPrim::CPoint &perspective) const;
      //    void ReOrient(std::vector<Mesh::IndexType> &ec);
      GeoPrim::C3Point Centroid(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc) const;
      void shape_func(const GeoPrim::CVector &,
                      double []) const;
      void dshape_func(const GeoPrim::CVector &,
                       double [][2]) const;
      void jacobian(const GeoPrim::CPoint p[],
                    const GeoPrim::CVector &,
                    GeoPrim::CVector J[]) const;
      void interpolate(const GeoPrim::CVector f[],
                       const GeoPrim::CVector &nc,
                       GeoPrim::CVector &) const;
      void GetNormalSet(GeoPrim::CVector ns[],
                        Mesh::IndexType elnum,
                        const Connectivity &ec,
                        const NodalCoordinates &nc);
      void GetPointSet(GeoPrim::CPoint ps[],
                       Mesh::IndexType elnum,
                       const Connectivity &ec,
                       const NodalCoordinates &nc);
      void shapef_jacobian_at(const GeoPrim::CPoint &p,
                              GeoPrim::CVector &natc, // size 2
                              Mesh::IndexType elnum,
                              const Connectivity &ec,
                              const NodalCoordinates &nc,
                              GeoPrim::CVector &fvec,
                              GeoPrim::CVector jac[]) const;
    };

    // Class to encapsulate all the element specific methods
    // Should be renamed to generic cell
    class GenericElement {
    protected:
      Mesh::IndexType _size; // Number of nodes
    public:
      GenericElement(Mesh::IndexType s = 4)
        : _size(s)
      {};
      void init(Mesh::IndexType s = 4)
      {
        _size = s;
      };
      Mesh::IndexType size() const
      {
        return(_size);
      };
      GeoPrim::C3Point Centroid();
      void Centroid(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc,GeoPrim::C3Point &centroid) const;
      Mesh::IndexType nedges() const
      {
        switch(_size){
        case 4:
        case 10:
          // tet
          return (6);
        case 8:
        case 20:
          // hex
          return (12);
        case 5:
        case 13:
          // pyr
          return(8);
        case 6:
        case 15:
          // pris
          return(9);
        default:
          return(0);
        }
        return(0);
      };
      Mesh::IndexType nfaces() const
      {
        switch(_size){
        case 4:
        case 10:
          // tet
          return(4);
        case 8:
        case 20:
          // hex
          return(6);
        case 5:
        case 13:
          // pyr
          return(5);
        case 6:
        case 15:
          // pris
          return(5);
        default:
          return(0);
        }
        return(0);
      };

      bool Inverted(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc) const;
      bool ShapeOK(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc) const;
      void ReOrient(std::vector<Mesh::IndexType> &ec);
      GeoPrim::C3Point Centroid(std::vector<Mesh::IndexType> &ec,NodalCoordinates &nc) const;

      ///
      /// \brief Face conn for given element
      ///
      /// Returns a vector of lists where each list is the face
      /// connectivity for the i'th face of the element, and i
      /// is the index into the vector.  This function was created
      /// as a utility for building overarching face containers for
      /// the whole mesh (on this processor).
      ///
      void get_face_connectivities(Connectivity &,
                                   const std::vector<Mesh::IndexType> &) const;

      //     double signed_element_volume(std::vector<Mesh::IndexType> &sec,
      // 				 NodalCoordinates &nc) const
      //     {
      //       switch(_size){
      //       case 4:
      //       case 10: // tet

      // 	return (6);
      //       case 8:
      //       case 20:
      // 	// hex
      // 	return (12);
      //       case 5:
      //       case 13:
      // 	// pyr
      // 	return(8);
      //       case 6:
      //       case 15:
      // 	// pris
      // 	return(9);
      //       default:
      // 	return(0);
      //       }
      //       return(0);

      //     };

      void shape_func(const GeoPrim::CVector &,
                      double []) const;
      void dshape_func(const GeoPrim::CVector &,
                       double [][3]) const;
      void jacobian(const GeoPrim::CPoint p[],
                    const GeoPrim::CVector &nc,
                    GeoPrim::CVector J[]) const;
      void interpolate(const GeoPrim::CVector f[],
                       const GeoPrim::CVector &nc,
                       GeoPrim::CVector &) const;
      void shapef_jacobian_at(const GeoPrim::CPoint &p,
                              GeoPrim::CVector &natc,
                              Mesh::IndexType elnum,
                              const Connectivity &ec,
                              const NodalCoordinates &nc,
                              GeoPrim::CVector &fvec,
                              GeoPrim::CVector fjac[]) const;
    };

    int GetMeshCentroids(Mesh::NodalCoordinates &nc,
                         Mesh::Connectivity     &conn,
                         std::vector<double>    &centroids);

    int CollideCellsWithBox(Mesh::NodalCoordinates &nc,
                            Mesh::Connectivity     &conn,
                            GeoPrim::CBox          &box,
                            std::vector<Mesh::IndexType> &candidates,
                            std::vector<Mesh::IndexType> &cells);
    int CollideMeshWithBox(Mesh::NodalCoordinates &nc,
                           Mesh::Connectivity     &conn,
                           GeoPrim::CBox          &box,
                           std::vector<Mesh::IndexType> &cells);
  
    bool
    NewtonRaphson(GeoPrim::CVector &natc,
                  Mesh::IndexType elnum,
                  const GenericElement &el,
                  const Connectivity &ec,
                  const NodalCoordinates &nc,
                  const GeoPrim::CPoint &point);

    bool
    NewtonRaphson_2(GeoPrim::CVector &natc,
                    Mesh::IndexType elnum,
                    const GenericCell_2 &el,
                    const Connectivity &ec,
                    const NodalCoordinates &nc,
                    const GeoPrim::CPoint &point);

    bool
    LUDcmp(GeoPrim::CVector a[],
           int indx[]);

    void
    LUBksb(GeoPrim::CVector a[],
           int indx[],
           GeoPrim::CVector &b);

    void GetCoordinateBounds(NodalCoordinates &nc,std::vector<double> &);

    void
    GetMeshBoxes(const NodalCoordinates &nc,
                 const Connectivity &ec,
                 GeoPrim::CBox &mesh_box,
                 GeoPrim::CBox &small_box,
                 GeoPrim::CBox &large_box);
    void
    FindElementsInBox(const GeoPrim::CBox &box,
                      const NodalCoordinates &nc,
                      const Connectivity &dc,  // dual connectivity
                      std::list<Mesh::IndexType> &elements);
    Mesh::IndexType
    FindPointInCells(const GeoPrim::CPoint &p, // Target point
                     const NodalCoordinates &nc, // Source
                     const Connectivity &ec, // Source connectivity
                     const std::vector<Mesh::IndexType> &elements,    // candidate cells
                     GeoPrim::CVector &natc);  // Returns Targ nat

    Mesh::IndexType
    GlobalFindPointInMesh(const GeoPrim::CPoint &p,      // Target Mesh point
                          const NodalCoordinates &nc,    // Source
                          const Connectivity &ec, // Source
                          const Connectivity &dc,    // Source
                          const GeoPrim::CBox &box,      // Source
                          GeoPrim::CVector &natc);  // Returns Targ nat
    Mesh::IndexType
    FindPointInMesh_2(const GeoPrim::CPoint &p, // Target Mesh point
                      const NodalCoordinates &nc, // Source
                      const Connectivity &ec, // Source connectivity
                      const Connectivity &dc,    // Source dual connectivity
                      const GeoPrim::CBox &box,    // Source
                      GeoPrim::CVector &natc);  // Returns Targ nat

    Mesh::IndexType
    FindPointInMesh(const GeoPrim::CPoint &p, // Target Mesh point
                    const NodalCoordinates &nc, // Source
                    const Connectivity &ec, // Source connectivity
                    const Connectivity &dc,    // Source dual connectivity
                    const GeoPrim::CBox &box,    // Source
                    GeoPrim::CVector &natc);  // Returns Targ nat



    class SolnMetaData {
    public:
      std::string name;
      char loc;
      std::string unit;
      unsigned int ncomp;
      unsigned int dsize;
    };
  
    class Stats {
    public:
      double maximum_volume;
      double minimum_volume;
      double mean_volume;
      Mesh::IndexType n_triangles;
      Mesh::IndexType n_quads;
      Mesh::IndexType n_tets;
      Mesh::IndexType n_pyrs;
      Mesh::IndexType n_pris;
      Mesh::IndexType n_hex;
      Mesh::IndexType n_tri_faces;
      Mesh::IndexType n_quad_faces;
      Mesh::IndexType n_tri_boundary_faces;
      Mesh::IndexType n_quad_boundary_faces;
      GeoPrim::C3Box  min_box;
      GeoPrim::C3Box  max_box;
      GeoPrim::C3Box  bounding_box;
    };
  } // Namespace MESH 
} // Namespace SolverUtils
#endif



